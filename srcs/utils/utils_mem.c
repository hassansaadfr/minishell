#include "minishell.h"

void	free_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		free_split(cmds[i++]);
	ft_free_ptr((void **)&cmds);
}

void	free_env(t_list **env_list)
{
	t_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		ft_free_ptr(((void **)&((t_env *)tmp->content)->name));
		ft_free_ptr(((void **)&((t_env *)tmp->content)->value));
		tmp = tmp->next;
	}
	ft_lstclear(env_list, free);
	env_list = NULL;
}

void	free_token(void *content)
{
	char	*arg;

	arg = ((t_token *)content)->arg;
	if (arg)
		ft_free_ptr((void **)&arg);
	ft_free_ptr((void **)&content);
}

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_alloc(new_size);
	ft_bzero(new_ptr, new_size);
	ft_memcpy(new_ptr, old_ptr, old_size);
	ft_free_ptr((void **)&old_ptr);
	return (new_ptr);
}

void	free_splitted_pipeline(t_cmd_and_redir *splitted_pipeline,
		int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (splitted_pipeline[i].cmd)
			ft_lstclear(&splitted_pipeline[i].cmd, free_token);
		if (splitted_pipeline[i].redirs)
			ft_lstclear(&splitted_pipeline[i].redirs, free_token);
		i++;
	}
}
