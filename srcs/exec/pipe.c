#include "minishell.h"

int	is_empty(char *buff)
{
	return (*buff == '\0');
}

int	display_err_ret_err(char *problem_pos, char *err_msg, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (problem_pos && is_empty(problem_pos) == FALSE)
	{
		ft_putstr_fd(problem_pos, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (err);
}

int wait_all_pids(int *pids, int cmd_count)
{
	int     i;
	int     return_code;

	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] == -1)
			i++;
		else if (waitpid(pids[i++], &return_code, 0) == -1)
			display_err_ret_err("waitpid", strerror(errno), 125 + errno);
	}
	return (return_code);
}

int add_child_proc(char **cmd, int *in_out_tbc, char **envp, t_list *redirs)
{
	int     pid;

	pid = fork();
	if (pid == -1) 
		return (display_err_ret_err("fork", strerror(errno), 125 + errno));
	else if (pid == 0)
	{
	// USE HERE A MODIFIED VERSION OF execution() -- exec.c
		perform_pipeline_redirections(redirs, in_out_tbc);	// PROTECT
		if (in_out_tbc[TBC] >= 0)
			close(in_out_tbc[TBC]);
		dup2(in_out_tbc[IN], STDIN_FILENO); 				// PROTECT
		dup2(in_out_tbc[OUT], STDOUT_FILENO);				// PROTECT
		if (cmd == NULL || cmd[0] == NULL)
			exit(0);
		if (execve(cmd[0], cmd, envp) == -1) 
			ft_exit_free(125 + errno);
	}
	return (pid);
}

void    assign_in_out_tbc(int cmd_count, int i, int *in_out_tbc, int *fds)
{
	if (i < cmd_count - 1)
	{
		in_out_tbc[OUT] = fds[1];
		in_out_tbc[TBC] = fds[0];
	}
	else
	{   
		in_out_tbc[OUT] = STDOUT_FILENO;
		in_out_tbc[TBC] = -1; 
	}   
}

int	pipeline_execution(t_cmd_and_redir *cmds, t_list *env_list,
		int cmd_count)
{
	t_pipe	p;
	int		error = -1;

	init_pipe_struct(&p, cmd_count, env_list);
	while (p.i < cmd_count)
	{
		if (p.i < cmd_count - 1)
		{
			if (pipe(p.pipe_fds) == -1)
				return (error);
		}
		assign_in_out_tbc(cmd_count, p.i, p.in_out_tbc, p.pipe_fds);
		p.cmd = token_list_to_array(cmds[p.i].cmd); // PASS IN CHILD
		if (p.cmd && p.cmd[0])						// PASS IN CHILD
			search_bin(p.cmd, env_list);			// PASS IN CHILD
		p.pids[p.i] = add_child_proc(p.cmd, p.in_out_tbc, p.envp, cmds[p.i].redirs);
		close(p.in_out_tbc[IN]);
		if (p.i < cmd_count - 1)
			close(p.pipe_fds[1]);
		p.in_out_tbc[IN] = p.pipe_fds[0];
		p.i++;
	}
	close(p.pipe_fds[0]);
	p.return_code = wait_all_pids(p.pids, cmd_count);
	restore_fds(p.old_fds);
	return (p.return_code);
}

int execute_pipeline(t_list *pipeline, t_list *env_list)
{
	int             cmd_count;
	int				ret_exec;
	t_cmd_and_redir *splitted_pipeline;

	ret_exec = 0;
	cmd_count = count_pipes(pipeline) + 1;
	splitted_pipeline = ft_alloc(sizeof(t_cmd_and_redir) * (cmd_count + 1));
	init_splitted_pipeline(splitted_pipeline, cmd_count);
	split_pipeline(pipeline, splitted_pipeline);
	expand_pipeline(splitted_pipeline, cmd_count, env_list);
	ret_exec = pipeline_execution(splitted_pipeline, env_list, cmd_count);
	free_splitted_pipeline(splitted_pipeline, cmd_count);
	ft_free_ptr((void **)&splitted_pipeline);
	return (ret_exec);
}
