#include "minishell.h"

t_list		*init_env(char **envp)
{
	t_list	*env_list;
	int		envp_size;

	env_list = NULL;
	envp_size = get_strarr_size(envp);
	if (envp_size > 0)
	{
		env_list = ft_lstnew(ft_strdup(*envp));
		if (!env_list)
			return (NULL);
		if (envp_size > 1)
		{
			envp++;
			while (*envp)
				ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(*envp++)));
			return (env_list);
		}
	}
	return (env_list);
}

t_list		*get_env(t_list *env_list, char *name)
{
	t_list	*tmp;
	char	**splitted;

	tmp = env_list;
	while (tmp && name)
	{
		splitted = ft_split(tmp->content, '=');
		if (ft_strncmp(splitted[0], name, ft_strlen(name) + 1) == 0)
		{
			free_split(splitted);
			return (tmp);
		}
		tmp = tmp->next;
		free_split(splitted);
	}
	return (NULL);
}

/*
** TODO
** check ft_split return with errno
*/

int			new_env(t_list *env_list, char *new_env)
{
	t_list	*tmp;
	char	**splitted;
	int		out;

	out = 0;
	splitted = ft_split(new_env, '=');
	if (!splitted)
		return (0);
	tmp = get_env(env_list, splitted[0]);
	if (!tmp)
	{
		ft_lstadd_back(&env_list, ft_lstnew(new_env));
		out = 1;
	}
	free_split(splitted);
	return (out);
}

/*
** TODO
** check ft_split return with errno
*/

int			edit_env(t_list *env_list, char *env)
{
	char	**splitted;
	t_list	*tmp;
	int		size;

	if (!env)
		return (0);
	splitted = ft_split(env, '=');
	size = get_strarr_size(splitted);
	if (size != 2)
	{
		free_split(splitted);
		return (0);
	}
	tmp = get_env(env_list, splitted[0]);
	if (tmp)
	{
		free(tmp->content);
		tmp->content = ft_strdup(env);
		free_split(splitted);
		return (1);
	}
	free_split(splitted);
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
