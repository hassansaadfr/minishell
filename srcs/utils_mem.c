#include "minishell.h"

void	free_split(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i] != NULL)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	free_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		free_split(cmds[i++]);
	free(cmds);
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
