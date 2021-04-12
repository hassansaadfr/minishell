#include "minishell.h"

t_list		*init_env(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	char	*dupped;

	env_list = NULL;
	new_node = NULL;
	while (envp != NULL && *envp != NULL)
	{
		dupped = ft_strdup(*envp);
		new_node = ft_lstnew(dupped);
		if (!new_node || !dupped)
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

	i = 0;
	tmp = env_list;
	if (!name)
		return (NULL);
	while (name[i])
	{
		if (ft_isalnum(name[i]))
			i++;
		else
			return (NULL);
	}
	while (tmp && name)
	{
		len = ft_strchr(tmp->content, '=') - (char*)tmp->content;
		if (ft_strncmp(tmp->content, name, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			new_env(t_list *env_list, char *new_env)
{
	t_list	*tmp;
	int		out;
	char	*equals_pos;

	out = 0;
	if (!new_env)
		return (0);
	equals_pos = ft_strchr(new_env, '=');
	if (equals_pos)
	{
		*equals_pos = '\0';
		tmp = NULL;
		tmp = get_env(env_list, new_env);
		if (!tmp)
		{
			*equals_pos = '=';
			ft_lstadd_back(&env_list, ft_lstnew(new_env));
			out = 1;
		}
	}
	return (out);
}

int			edit_env(t_list *env_list, char *env)
{
	t_list	*tmp;
	char	*equals_pos;

	if ((!env || !ft_strchr(env, '=')))
		return (0);
	if (env[0] == '=')
		return (0);
	equals_pos = ft_strchr(env, '=');
	if (equals_pos)
	{
		*equals_pos = '\0';
		tmp = get_env(env_list, env);
		if (tmp)
		{
			*equals_pos = '=';
			tmp->content = env;
			return (1);
		}
	}
	return (0);
}

int			delete_env(t_list *env_list, char *name)
{
	t_list	*tmp;
	int		out;

	tmp = NULL;
	out = 0;
	if (name)
		tmp = get_env(env_list, name);
	if (tmp)
	{
		ft_lstdelone(tmp, free);
		out = 1;
	}
	return (out);
}
