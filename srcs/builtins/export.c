#include "minishell.h"

static void	print_env_list(t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		ft_putstr_fd((((t_env*)tmp->content)->name), STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd((((t_env*)tmp->content)->value), STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

static char	*standardize_env(char *env)
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
			done = new_env(env_list, env);
			if (!done)
				done = edit_env(env_list, env);
			free(env);
			i++;
		}
	}
	return (done);
}
