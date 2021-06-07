#include "minishell.h"

int			unset(char *argv, t_list *env_list)
{
	char	*name;
	int		out;

	name = parse_env_name(argv);
	out = 0;
	if (!is_valid_env_name(name, "unset"))
		out = 1;
	out = delete_env(env_list, argv);
	ft_free_ptr((void**)&name);
	return (out);
}

int			builtin_unset(char **argv, t_list *env_list)
{
	int		out;
	int		i;

	i = 1;
	while (argv[i])
		out = unset(argv[i++], env_list);
	printf("out %d\n", out);
	return (out);
}
