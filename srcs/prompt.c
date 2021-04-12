#include "minishell.h"

void	prompt(t_list *env_list)
{
	t_list	*tmp;
	char	*env_val;

	env_val = NULL;
	tmp = get_env(env_list, "PWD");
	if (!tmp)
		return ;
	env_val = ft_strchr(tmp->content, '=') + 1;
	if (isatty(0))
	{
		ft_putstr_fd(env_val, 2);
		ft_putstr_fd("$> ", 2);
	}
}
