#include "minishell.h"

static t_env	**tlist_to_arr_of_tenv(t_list *env_list)
{
	int		i;
	int		size;
	t_env	**out;

	i = 0;
	size = 0;
	size = ft_lstsize(env_list);
	out = ft_alloc(sizeof(t_env) * (size + 1));
	out[size] = NULL;
	while (env_list)
	{
		out[i] = ((t_env *)env_list->content);
		i++;
		env_list = env_list->next;
	}
	return (out);
}

static void	sort(t_env **array, int start, int end)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = start;
	while (i <= end - 1)
	{
		j = i + 1;
		while (j <= end)
		{
			if (ft_strcmp(array[i]->name, array[j]->name) > 0)
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_env_list(t_list *env_list)
{
	t_env	**env_arr;
	int		i;
	int		size;

	size = ft_lstsize(env_list);
	i = 0;
	env_arr = tlist_to_arr_of_tenv(env_list);
	sort(env_arr, 0, size - 1);
	while (i < size)
	{
		if (ft_strcmp("_", env_arr[i]->name) != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env_arr[i]->name, STDOUT_FILENO);
			if (env_arr[i]->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(env_arr[i]->value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	ft_free_ptr((void **)&env_arr);
}

int	can_export(char *name)
{
	int		out;
	char	*env_name;

	env_name = NULL;
	out = 0;
	if (name[0] == '-')
	{
		out = 2;
		print_err_with_quote("export", name, INVALID_IDENTIFIER_FR);
	}
	else
	{
		env_name = parse_env_name(name);
		if (env_name == NULL)
			out = 1;
		else
			out = is_valid_env_name(env_name, "export");
	}
	ft_free_ptr((void **)&env_name);
	return (out);
}

int	builtin_export(char **argv, t_list *env_list)
{
	int		out;

	out = 0;
	if (get_strarr_size(argv) == 1)
		print_env_list(env_list);
	else
	{
		argv++;
		while (*argv)
		{
			out = can_export(*argv);
			if (out == 0)
			{
				if (new_env(env_list, *argv) == 0)
					out = edit_env(env_list, *argv);
			}
			argv++;
		}
	}
	return (out);
}
