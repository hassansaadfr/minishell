#include "minishell.h"

int		exec_from_builtins(char **argv, t_list *env_list)
{
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd(argv, env_list));
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(argv, env_list));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(argv, env_list));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(argv, env_list));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit(argv, env_list));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(argv, env_list));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (env(env_list));
	return (0);
}

int		is_builtin(char **argv)
{
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (1);
	return (0);
}
