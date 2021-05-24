#include "minishell.h"

int			unset(char *argv, t_list *env_list)
{
	if (!is_valid_env_name(argv, "unset"))
		return (0);
	return (delete_env(env_list, argv));
}

int			builtin_unset(char **argv, t_list *env_list)
{
	int		out;
	int		i;

	i = 1;
	while (argv[i])
		out = unset(argv[i++], env_list);
	return (out);
}
