#include "minishell.h"

int	builtin_unset(char **argv, t_list *env_list)
{
	int		out;
	int		i;

	out = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			out = 2;
		else if (is_valid_env_name(argv[i], "unset") == 0)
			delete_env(env_list, argv[i]);
		else
			out = 1;
		i++;
	}
	return (out);
}
