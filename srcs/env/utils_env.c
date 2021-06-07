#include "minishell.h"

t_list	*get_env(t_list *env_list, char *name)
{
	t_list	*tmp;
	int		i;
	int		len;
	char	*parsed_name;

	i = 0;
	tmp = env_list;
	if (!name)
		return (NULL);
	parsed_name = parse_env_name(name);
	if (!parsed_name)
		return (NULL);
	while (tmp)
	{
		len = ft_strlen(parsed_name) + 1;
		if (ft_strncmp(((t_env *)tmp->content)->name,
				parsed_name, len + 1) == 0)
		{
			ft_free_ptr((void **)&parsed_name);
			return (tmp);
		}
		tmp = tmp->next;
	}
	ft_free_ptr((void **)&parsed_name);
	return (NULL);
}

int	new_env(t_list *env_list, char *new_env)
{
	t_list	*tmp;
	int		out;
	t_list	*env_node;
	char	*parsed_name;

	out = 0;
	if (!new_env)
		return (0);
	tmp = NULL;
	parsed_name = parse_env_name(new_env);
	tmp = get_env(env_list, parsed_name);
	if (!tmp)
	{
		env_node = init_env_node(new_env);
		if (!env_node)
		{
			ft_free_ptr((void **)&parsed_name);
			return (0);
		}
		ft_lstadd_back(&env_list, env_node);
		out = 1;
	}
	ft_free_ptr((void **)&parsed_name);
	return (out);
}

int	edit_env(t_list *env_list, char *env)
{
	t_list	*tmp;
	t_env	*env_node;

	if (!env)
		return (0);
	if (env[0] == '=')
		return (0);
	tmp = get_env(env_list, env);
	if (tmp)
	{
		env_node = tmp->content;
		if (env_node->value)
			ft_free_ptr((void **)&env_node->value);
		env_node->value = parse_env_value(env);
		return (1);
	}
	return (0);
}

int	delete_env(t_list *env_list, char *name)
{
	t_list	*tmp;
	int		out;
	char	*env_name;

	env_name = NULL;
	if (name == NULL || ft_strchr(name, '='))
		return (0);
	if (name)
		env_name = parse_env_name(name);
	tmp = NULL;
	out = 0;
	if (env_name)
		tmp = get_env(env_list, env_name);
	if (tmp)
	{
		ft_free_ptr((void **)&((t_env *)tmp->content)->name);
		ft_free_ptr((void **)&((t_env *)tmp->content)->value);
		ft_free_ptr((void **)&env_name);
		ft_lstdelone(&tmp, free_env_node);
		out = 1;
	}
	return (out);
}

char	*get_env_value(t_list *env_list, char *name)
{
	char	*value;
	t_list	*tmp;
	t_env	*env;

	value = NULL;
	tmp = NULL;
	tmp = get_env(env_list, name);
	if (tmp)
	{
		env = tmp->content;
		if (env->value)
			value = env->value;
	}
	return (value);
}
