#include "minishell.h"

int			builtin_echo(char **argv, t_list *env_list)
{
	int		i;
	int		nl;
	int		nb_arg;

	i = 0;
	nl = 0;
	(void)env_list;
	argv++;
	if (*argv && ft_strncmp(argv[0], "-n", 3) == 0)
	{
		nl = 1;
		argv++;
	}
	nb_arg = get_strarr_size(argv);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < nb_arg - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
