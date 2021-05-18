#include "minishell.h"

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
		ft_lstadd_back(&env_list, new_node);
		envp++;
	}
	return (env_list);
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
	name = parse_env_name(env);
	value = parse_env_value(env);
	env_node->name = name;
	env_node->value = value;
	list_node = ft_lstnew(env_node);
	return (list_node);
}

void		free_env_node(void *ptr)
{
	ft_free_ptr((void**)&ptr);
}
