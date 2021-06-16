#include "minishell.h"

int	init_pipe_struct(t_fds *p, int cmd_count, t_list *env_list)
{
	int		i;

	p->i = 0;
	p->in_out_tbc[IN] = STDIN_FILENO;
	p->cmd = NULL;
	p->envp = list_to_array(env_list);
	p->pids = ft_alloc(sizeof(int) * cmd_count);
	if (backup_std(p->old_fds) != 0)
	{
		ft_free_ptr((void **)&p->pids);
		return (1);
	}
	i = 0;
	while (i < cmd_count)
		p->pids[i++] = -1;
	return (0);
}

int	backup_std(int *old_fds)
{
	errno = 0;

	old_fds[IN] = dup(STDIN_FILENO);
	if (old_fds[IN] == -1)
		return (display_err_ret_err("dup", strerror(errno), 1));
	old_fds[OUT] = dup(STDOUT_FILENO);
	if (old_fds[OUT] == -1)
		if (old_fds[OUT] == -1)
	{
		close(old_fds[IN]);
		return (display_err_ret_err("dup", strerror(errno), 1));
	}
	return (0);
}

int	restore_fds(int *old_fds)
{
	dup2(old_fds[IN], STDIN_FILENO);
	// PROTECT
	dup2(old_fds[OUT], STDOUT_FILENO);
	// PROTECT
	close(old_fds[IN]);
	// PROTECT
	close(old_fds[OUT]);
	// PROTECT
	return (0);
}
