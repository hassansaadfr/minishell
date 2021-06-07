#include "minishell.h"

static void	print_env_list(t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (((t_env *)tmp->content)->value != NULL)
		{
			ft_putstr_fd((((t_env *)tmp->content)->name), STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd((((t_env *)tmp->content)->value), STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
}

int	env(t_list *env_list)
{
	print_env_list(env_list);
	return (0);
}
