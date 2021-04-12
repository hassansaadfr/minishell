#include "minishell.h"

int		env(t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (1);
}
