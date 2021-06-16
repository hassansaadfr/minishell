#include "minishell.h"

int	display_err_ret_err(char *problem_pos, char *err_msg, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (problem_pos && not_empty(problem_pos) == TRUE)
	{
		ft_putstr_fd(problem_pos, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (err);
}

int	wait_all_pids(int *pids, int cmd_count)
{
	int	i;
	int	return_code;
	int	ret;

	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] == -1)
			i++;
		else
		{
			ret = waitpid(pids[i++], &return_code, 0);
			if (WIFEXITED(return_code))
				return_code = WEXITSTATUS(return_code);
		}
	}
	return (return_code);
}

/*	PROTECT - perform_pipeline_redirections() */
/*	PROTECT - dup2() */
/*	PROTECT - dup2() */
/*	MODIF - one_pipe_exec() was an execve(cmd[0], cmd, envp) BEFORE */

int	add_child_proc(t_list *cmd_list, int *in_out_tbc, t_list *env_list,
		t_list *redirs)
{
	int		pid;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		return (display_err_ret_err("fork", strerror(errno), 125 + errno));
	else if (pid == 0) // CHILD
	{
		errno = 0;
		if (perform_pipeline_redirections(redirs, in_out_tbc) != 0)	// PROTECT
			ft_exit_free(14 + errno);
		if (in_out_tbc[TBC] >= 0)
			close(in_out_tbc[TBC]);
		dup2(in_out_tbc[IN], STDIN_FILENO);					//	PROTECT
		dup2(in_out_tbc[OUT], STDOUT_FILENO);				//	PROTECT
		cmd = token_list_to_array(cmd_list);
		if (cmd == NULL || cmd[0] == NULL)
			exit(0);
		if (cmd && cmd[0])
			one_pipe_exec(cmd, env_list, NULL);
	}
	return (pid);
}

void	assign_in_out_tbc(int cmd_count, int i, int *in_out_tbc, int *fds)
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

int	pipeline_execution(t_pipeline *cmds, t_list *env_list, int cmd_count, int *error)
{
	(void)error;
	t_fds	p;

	if (init_pipe_struct(&p, cmd_count, env_list) != 0)
		return (1);
	while (p.i < cmd_count)
	{
		errno = 0;
		if (p.i < cmd_count - 1)
		{
			if (pipe(p.pipe_fds) == -1)
			{
				close(p.old_fds[IN]);
				close(p.old_fds[OUT]);
				return (display_err_ret_err("pipe", strerror(errno), 1));
			}
		}
		assign_in_out_tbc(cmd_count, p.i, p.in_out_tbc, p.pipe_fds);
		p.pids[p.i] = add_child_proc(cmds[p.i].cmd,
				p.in_out_tbc, env_list, cmds[p.i].redirs); // PROTECT
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

int	execute_pipeline(t_list *pipeline, t_list *env_list)
{
	int				cmd_count;
	int				ret_exec;
	int				error;
	t_pipeline		*pipes_arr;

	ret_exec = 0;
	cmd_count = count_pipes(pipeline) + 1;
	pipes_arr = ft_alloc(sizeof(t_pipeline) * (cmd_count + 1));
	init_splitted_pipeline(pipes_arr, cmd_count);
	split_pipeline(pipeline, pipes_arr);
	expand_pipeline(pipes_arr, cmd_count, env_list);
	error = 0;
	ret_exec = pipeline_execution(pipes_arr, env_list, cmd_count, &error);//PROT
	free_splitted_pipeline(pipes_arr, cmd_count);
	ft_free_ptr((void **)&pipes_arr);
	return (ret_exec);
}
