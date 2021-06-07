#include "minishell.h"

int	exec_from_builtins(char **argv, t_list *env_list, t_list *history)
{
	if (ft_strcmp(*argv, "history") == 0)
		return (builtin_history(argv, env_list, history));
	if (ft_strcmp(*argv, "pwd") == 0)
		return (builtin_pwd(argv, env_list));
	if (ft_strcmp(*argv, "echo") == 0)
		return (builtin_echo(argv, env_list));
	if (ft_strcmp(*argv, "unset") == 0)
		return (builtin_unset(argv, env_list));
	if (ft_strcmp(*argv, "export") == 0)
		return (builtin_export(argv, env_list));
	if (ft_strcmp(*argv, "exit") == 0)
		return (builtin_exit(argv, env_list));
	if (ft_strcmp(*argv, "cd") == 0)
		return (builtin_cd(argv, env_list));
	if (ft_strcmp(*argv, "env") == 0)
		return (env(env_list));
	return (0);
}

int	is_builtin(char **argv)
{
	if (ft_strcmp(*argv, "pwd") == 0)
		return (1);
	if (ft_strcmp(*argv, "echo") == 0)
		return (1);
	if (ft_strcmp(*argv, "unset") == 0)
		return (1);
	if (ft_strcmp(*argv, "export") == 0)
		return (1);
	if (ft_strcmp(*argv, "exit") == 0)
		return (1);
	if (ft_strcmp(*argv, "cd") == 0)
		return (1);
	if (ft_strcmp(*argv, "env") == 0)
		return (1);
	if (ft_strcmp(*argv, "history") == 0)
		return (1);
	return (0);
}
