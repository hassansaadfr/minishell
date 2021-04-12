#include "minishell.h"

void	free_split(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	ft_lstclear(env_list, free);
	env_list = NULL;
}
