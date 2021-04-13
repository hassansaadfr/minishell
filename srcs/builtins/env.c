#include "minishell.h"

void	print_env_list(t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int		env(t_list *env_list)
{
	print_env_list(env_list);
	return (1);
}
