#include "minishell.h"

int			ft_unset_error(char **argv)
{
	int		size;

	size = 0;
	size = get_strarr_size(argv);
	if (size == 1)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (0);
	}
	return (1);
}

int			unset(char *argv, t_list *env_list)
{
	return (delete_env(env_list, argv));
}

int			builtin_unset(char **argv, t_list *env_list)
{
	int		out;
	int		i;

	out = ft_unset_error(argv);
	if (out)
	{
		i = 1;
		while (argv[i])
			unset(argv[i++], env_list);
	}
	return (out);
}
