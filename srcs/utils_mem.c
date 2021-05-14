#include "minishell.h"

void	free_split(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i] != NULL)
	{
		ft_free_ptr((void**)&splitted[i]);
		i++;
	}
	ft_free_ptr((void**)&splitted);
}

void	free_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		free_split(cmds[i++]);
	ft_free_ptr((void**)&cmds);
}

void	free_env(t_list **env_list)
{
	t_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		free(((t_env*)tmp->content)->name);
		free(((t_env*)tmp->content)->value);
		tmp = tmp->next;
	}
	ft_lstclear(env_list, free);
	env_list = NULL;
}

void	free_token(void *content)
{
	char	*arg;

	arg = ((t_token*)content)->arg;
	if (arg)
		free(arg);
	free(content);
}

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		free(old_ptr);
		return (NULL);
	}
	ft_bzero(new_ptr, new_size);
	ft_memcpy(new_ptr, old_ptr, old_size);
	free(old_ptr);
	return (new_ptr);
}
