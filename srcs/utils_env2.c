#include "minishell.h"

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
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	name = parse_env_name(env);
	value = parse_env_value(env);
	env_node->name = name;
	env_node->value = value;
	list_node = ft_lstnew(env_node);
	return (list_node);
}
