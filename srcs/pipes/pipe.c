#include "minishell.h"

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

int	add_child_proc(t_pipeline one_pipe, int *in_out_tbc, t_list *env_list)
{
	int		pid;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		return (return_err_msg("fork", strerror(errno), 125 + errno));
	else if (pid == 0)
	{
		errno = 0;
		if (perform_pipeline_redirections(one_pipe.redirs, in_out_tbc) != 0)
			ft_exit_free(125 + errno);
		if (in_out_tbc[TBC] >= 0)
			close(in_out_tbc[TBC]);
		if (dup2(in_out_tbc[IN], STDIN_FILENO) == -1)
			ft_exit_free(return_err_msg("dup2", strerror(errno), errno + 125));
		if (dup2(in_out_tbc[OUT], STDOUT_FILENO) == -1)
			ft_exit_free(return_err_msg("dup2", strerror(errno), errno + 125));
		cmd = token_list_to_array(one_pipe.cmd);
		if (cmd == NULL || cmd[0] == NULL)
			exit(0);
		if (cmd && cmd[0])
			one_pipe_exec(cmd, env_list, NULL);
	}
	return (pid);
}

int	pipeline_execution(t_pipeline *cmds, t_list *env_list, int cmd_count)
{
	t_fds	p;

	if (init_pipe_struct(&p, cmd_count, env_list) != 0)
		return (1);
	while (p.i < cmd_count)
	{
		errno = 0;
		if (p.i < cmd_count - 1 && pipe(p.pipe_fds) == -1)
		{
			restore_fds(p.old_fds);
			return (return_err_msg("pipe", strerror(errno), 1));
		}
		assign_in_out_tbc(cmd_count, p.i, p.in_out_tbc, p.pipe_fds);
		p.pids[p.i] = add_child_proc(cmds[p.i], p.in_out_tbc, env_list);
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
	ret_exec = pipeline_execution(pipes_arr, env_list, cmd_count);
	free_splitted_pipeline(pipes_arr, cmd_count);
	ft_free_ptr((void **)&pipes_arr);
	return (ret_exec);
}
