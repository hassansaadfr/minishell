#include "minishell.h"

int	process_is_parent(void)
{
	if (g_global.pid > 0)
		return (PARENT_PID);
	else if (g_global.pid == 0)
		return (CHILD_PID);
	else
		return (ERROR_FORK);
}

int	init_pipe_struct(t_pipe *p, int cmd_count, t_list *env_list)
{
	int		i;

	p->i = 0;
	p->in_out_tbc[IN] = STDIN_FILENO;
	p->cmd = NULL;
	p->envp = list_to_array(env_list);
	p->pids = ft_alloc(sizeof(int) * cmd_count);
	backup_std(p->old_fds);
	// PROTECT
	i = 0;
	while (i < cmd_count)
		p->pids[i++] = -1;
	return (1);
}

int	backup_std(int *old_fds)
{
	old_fds[IN] = dup(STDIN_FILENO);
	// PROTECT
	old_fds[OUT] = dup(STDOUT_FILENO);
	// PROTECT
	return (1);
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
	return (1);
}
