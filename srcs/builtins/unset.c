#include "minishell.h"

int	unset(char *argv, t_list *env_list)
{
	int		out;

	out = 0;
	if (!is_valid_env_name(argv, "unset"))
		out = 1;
	out = delete_env(env_list, argv);
	return (out);
}

int	builtin_unset(char **argv, t_list *env_list)
{
	int		out;
	int		i;

	i = 1;
	while (argv[i])
		out = unset(argv[i++], env_list);
	return (out);
}
