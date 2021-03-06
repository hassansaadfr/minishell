#include "minishell.h"

static int	exec_bin(char *path, char **args, t_list *env_list)
{
	char	**envp;
	int		exec_ret;

	exec_ret = 0;
	envp = list_to_array(env_list);
	errno = 0;
	if (execve(path, args, envp) == -1)
		ft_exit_free(125 + errno);
	return (exec_ret);
}

int	one_pipe_exec(char **cmds, t_list *env_list, t_list *history)
{
	int		can_exec;
	int		return_value;
	char	*arg;

	arg = ft_strdup(*cmds);
	return_value = 0;
	if (is_builtin(cmds))
		ft_exit_free((exec_from_builtins(cmds, env_list, history)));
	else
	{
		can_exec = search_bin(cmds, env_list);
		if (can_exec == 0)
			return_value = exec_bin(cmds[0], cmds, env_list);
		else if (can_exec > 125)
		{
			return_value = can_exec;
			print_err(NULL, arg, strerror(can_exec - 125));
		}
		ft_free_ptr((void **)&arg);
		ft_exit_free(return_value);
	}
	return (return_value);
}
