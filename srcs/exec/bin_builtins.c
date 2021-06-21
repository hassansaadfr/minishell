#include "minishell.h"

int	exec_from_builtins(char **argv, t_list *env_list, t_list *history)
{
	int		out;

	if (ft_strcmp(*argv, "history") == 0)
		out = builtin_history(argv, env_list, history);
	if (ft_strcmp(*argv, "pwd") == 0)
		out = builtin_pwd(argv, env_list);
	if (ft_strcmp(*argv, "echo") == 0)
		out = builtin_echo(argv, env_list);
	if (ft_strcmp(*argv, "unset") == 0)
		out = builtin_unset(argv, env_list);
	if (ft_strcmp(*argv, "export") == 0)
		out = builtin_export(argv, env_list);
	if (ft_strcmp(*argv, "exit") == 0)
		out = builtin_exit(argv, env_list);
	if (ft_strcmp(*argv, "cd") == 0)
		out = builtin_cd(argv, env_list);
	if (ft_strcmp(*argv, "env") == 0)
		out = env(env_list);
	edit_underscore_var(env_list, argv[get_strarr_size(argv) - 1]);
	return (out);
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

void	edit_underscore_var(t_list *env_list, char *last_arg)
{
	edit_env(env_list, ft_strjoin("_=", last_arg));
}
