#include "minishell.h"

static char	*concat_name_value_env(t_list *list)
{
	char	*name;
	char	*value;
	char	*out;
	char	*tmp;

	errno = 0;
	name = ((t_env*)list->content)->name;
	value = ((t_env*)list->content)->value;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	out = ft_strjoin(tmp, value);
	ft_free_ptr((void**)&tmp);
	if (!out)
		return (NULL);
	return (out);
}

char		**list_to_array(t_list *env_list)
{
	char	**out;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!env_list)
		return (NULL);
	size = ft_lstsize(env_list);
	out = ft_alloc(sizeof(char*) * (size + 1));
	out[size] = 0;
	while (env_list)
	{
		out[i] = concat_name_value_env(env_list);
		if (!out[i])
		{
			free_split(out);
			return (NULL);
		}
		env_list = env_list->next;
		i++;
	}
	return (out);
}

char		*parse_env_name(char *env)
{
	char	*name;
	char	*equal_pos;

	name = NULL;
	equal_pos = NULL;
	if (!env)
		return (NULL);
	equal_pos = ft_strchr(env, '=');
	if (equal_pos == NULL)
		name = ft_strdup(env);
	if (equal_pos != NULL)
	{
		*equal_pos = '\0';
		if (ft_strlen(env) > 0)
			name = ft_strdup(env);
		*equal_pos = '=';
	}
	return (name);
}

char		*parse_env_value(char *env)
{
	char	*value;
	char	*equal_pos;

	value = NULL;
	equal_pos = NULL;
	if (!env)
		return (NULL);
	equal_pos = ft_strchr(env, '=');
	if (equal_pos != NULL)
		value = ft_strdup(equal_pos + 1);
	return (value);
}

int	is_valid_env_name(char *name, char *binary)
{
	int		i;
	char	*var_name;

	var_name = NULL;
	var_name = parse_env_name(name);
	if (var_name == NULL)
	{
		print_err_with_quote(binary, name, INVALID_IDENTIFIER_FR);
		return (1);
	}
	i = 0;
	while (var_name[i])
	{
		if (ft_isalnum(var_name[i]) || var_name[i] == '_')
			i++;
		else
		{
			if (isatty(STDIN_FILENO))
				print_err_with_quote(binary, var_name, INVALID_IDENTIFIER_FR);
			return (1);
		}
	}
	ft_free_ptr((void **)&var_name);
	return (0);
}
