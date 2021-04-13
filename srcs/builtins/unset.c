#include "minishell.h"

int			unset(char *argv, t_list *env_list)
{
	return (delete_env(env_list, argv));
}

int			builtin_unset(char **argv, t_list *env_list)
{
	int		out;
	int		i;

	i = 1;
	while (argv[i])
		unset(argv[i++], env_list);
	return (out);
}
