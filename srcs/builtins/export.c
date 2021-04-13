#include "minishell.h"

char		*standardize_env(char *env)
{
	char	*str;

	if (ft_strchr(env, '=') == NULL)
		str = ft_strjoin(env, "=");
	else
		str = ft_strdup(env);
	return (str);
}

int			builtin_export(char **argv, t_list *env_list)
{
	int		i;
	int		size;
	char	*env;
	int		done;

	done = 0;
	i = 1;
	size = get_strarr_size(argv);
	if (size == 1)
		print_env_list(env_list);
	else
	{
		while (argv[i])
		{
			env = standardize_env(argv[i]);
			done = new_env(env_list, ft_strdup(env));
			if (!done)
				done = edit_env(env_list, ft_strdup(env));
			free(env);
			i++;
		}
	}
	return (done);
}
