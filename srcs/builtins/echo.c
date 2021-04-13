#include "minishell.h"

char		*treat_argv(char *argv, t_list *env_list)
{
	char	*str;

	if (argv[0] == '$')
	{
		str = ft_strchr(get_env(env_list, argv + 1)->content, '=') + 1;
		return (str);
	}
	return (argv);
}

int			builtin_echo(char **argv, t_list *env_list)
{
	int		size;
	int		i;

	size = get_strarr_size(argv);
	if (size <= 1)
	{
		ft_putendl_fd("", 1);
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(treat_argv(argv[i], env_list), 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
	return (1);
}
