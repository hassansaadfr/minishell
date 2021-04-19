#include "minishell.h"

char		*parse_env_name(char *env)
{
	char	*name;
	char	*equal_pos;

	equal_pos = NULL;
	if (!env)
		return (NULL);
	name = env;
	equal_pos = ft_strchr(env, '=');
	if (equal_pos)
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
	if (equal_pos)
	{
		value = ft_strdup(equal_pos + 1);
	}
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
	list_node = malloc(sizeof(t_list));
	if (!list_node)
		return (NULL);
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	name = parse_env_name(env);
	value = parse_env_value(env);
	env_node->name = name;
	env_node->value = value;
	list_node->content = env_node;
	return (list_node);
}

t_list		*init_env(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	char	*name;
	char	*value;

	errno = 0;
	env_list = NULL;
	new_node = NULL;
	while (errno == 0 && (envp != NULL && *envp != NULL))
	{
		new_node = init_env_node(*envp);
		name = ((t_env*)new_node->content)->name;
		value = ((t_env*)new_node->content)->value;
		if (!new_node)
		{
			ft_lstclear(&env_list, free);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		envp++;
	}
	return (env_list);
}

t_list		*get_env(t_list *env_list, char *name)
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
	while (parsed_name[i])
	{
		if (ft_isalnum(parsed_name[i]))
			i++;
		else
			return (NULL);
	}
	while (tmp && parsed_name)
	{
		len = ft_strlen(parsed_name) + 1;
		if (ft_strncmp(((t_env*)tmp->content)->name, parsed_name, len + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			new_env(t_list *env_list, char *new_env)
{
	t_list	*tmp;
	int		out;
	t_list	*env_node;

	out = 0;
	if (!new_env)
		return (0);
	tmp = NULL;
	tmp = get_env(env_list, parse_env_name(new_env));
	if (!tmp)
	{
		env_node = init_env_node(new_env);
		if (!env_node)
			return (0);
		ft_lstadd_back(&env_list, env_node);
		out = 1;
	}
	return (out);
}

int			edit_env(t_list *env_list, char *env)
{
	t_list	*tmp;
	t_env	*new_node;

	if (!env)
		return (0);
	if (env[0] == '=')
		return (0);
	tmp = get_env(env_list, env);
	if (tmp)
	{
		if (((t_env*)tmp->content)->name)
			free(((t_env*)tmp->content)->name);
		if (((t_env*)tmp->content)->value)
			free(((t_env*)tmp->content)->value);
		free(tmp->content);
		new_node = ((t_env*)init_env_node(env)->content);
		if (new_node)
		{
			tmp->content = new_node;
			return (1);
		}
	}
	return (0);
}

int			delete_env(t_list *env_list, char *name)
{
	t_list	*tmp;
	int		out;
	char	*env_name;

	env_name = NULL;
	if (name == NULL || ft_strchr(name, '='))
		return (0);
	if (name)
		env_name =  parse_env_name(name);
	tmp = NULL;
	out = 0;
	if (env_name)
		tmp = get_env(env_list, env_name);
	if (tmp)
	{
		free(((t_env*)tmp->content)->name);
		free(((t_env*)tmp->content)->value);
		ft_lstdelone(tmp, free);
		out = 1;
	}
	return (out);
}
