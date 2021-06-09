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
		if (waitpid(pids[i++], &return_code, 0) == -1)
			return (display_err_ret_err("waitpid", strerror(errno), 125 + errno));
	}
	return (return_code);
}

int add_child_proc(char **cmd, int *in_out_tbc, char **envp)
{
	int     pid;

	pid = fork();
	if (pid == -1) 
		return (display_err_ret_err("fork", strerror(errno), 125 + errno));
	else if (pid == 0)
	{
		if (in_out_tbc[TBC] >= 0)
			close(in_out_tbc[TBC]);
		dup2(in_out_tbc[IN], STDIN_FILENO);
		dup2(in_out_tbc[OUT], STDOUT_FILENO);
		if (execve(cmd[0], cmd, envp) == -1) 
		{   
			display_err_ret_err(cmd[0], strerror(errno), 125 + errno);
			exit(errno);
		}   
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
	int		i;
	int		in_out_tbc[3];
	int		pipe_fds[2];
	int		old_fds[2];
	int		*pids;
	int		return_code;
	int		error = -1;
	char	**cmd;
	char	**envp;

	old_fds[IN] = dup(STDIN_FILENO);
	old_fds[OUT] = dup(STDOUT_FILENO);
	in_out_tbc[IN] = STDIN_FILENO;
	envp = list_to_array(env_list);
	pids = ft_alloc(sizeof(int) * cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1)
		{
			if (pipe(pipe_fds) == -1)
				return (error);
		}
		assign_in_out_tbc(cmd_count, i, in_out_tbc, pipe_fds);
		cmd = token_list_to_array(cmds[i].cmd);
		search_bin(cmd, env_list);
		pids[i] = add_child_proc(cmd, in_out_tbc, envp);
		close(in_out_tbc[IN]);
		if (i < cmd_count - 1)
			close(pipe_fds[1]);
		in_out_tbc[IN] = pipe_fds[0];
		i++;
	}
	close(pipe_fds[0]);
	return_code = wait_all_pids(pids, cmd_count);
	dup2(old_fds[IN], STDIN_FILENO);
	dup2(old_fds[OUT], STDOUT_FILENO);
	return (return_code);
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
	/*DBG*/printf("cmd_count = %d\n", cmd_count);
	/*DBG*/display_tokens(pipeline);
	split_pipeline(pipeline, splitted_pipeline);
	/*DBG*/display_splitted_pipeline(splitted_pipeline, cmd_count);
	pipeline_execution(splitted_pipeline, env_list, cmd_count);
	ft_free_ptr((void **)&splitted_pipeline);
	return (ret_exec);
}
