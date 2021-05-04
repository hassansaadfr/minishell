#include "minishell.h"

int		builtin_history(char **argv, t_list *env_list, t_list *history)
{
	int		i;
	int		size;
	t_list*	tmp;

	(void)env_list;
	size = 0;
	i = 0;
	tmp = ft_lstlast(history);
	size = get_strarr_size(argv);
	if (size == 1)
	{
		while (tmp)
		{
			ft_putnbr_fd(i++, STDOUT_FILENO);
			ft_putstr_fd("  ", STDOUT_FILENO);
			ft_putendl_fd(tmp->content, STDOUT_FILENO);
			tmp = tmp->previous;
		}
	}
	else
	{
		ft_putendl_fd("minishell: history: Argument list too long", STDERR_FILENO);
		return (0);
	}
	return (1);
}
