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
	// if (!out)
	// 	return (NULL);
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

t_list		*init_env_node(char *env)
{
	t_list	*list_node;
	t_env	*env_node;
	char	*name;
	char	*value;

	if (!env)
		return (NULL);
	env_node = ft_alloc(sizeof(t_env));
	// if (!env_node)
	// 	return (NULL);
	name = parse_env_name(env);
	value = parse_env_value(env);
	env_node->name = name;
	env_node->value = value;
	list_node = ft_lstnew(env_node);
	return (list_node);
}
