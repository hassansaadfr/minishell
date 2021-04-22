#include "minishell.h"

void	prompt(t_list *env_list, t_buff *buff)
{
	t_list	*tmp;
	char	*env_val;

	buff->pos = NULL;	
	(*buff->buffer) = '\0';
	env_val = NULL;
	tmp = get_env(env_list, "PWD");
	if (tmp)
		env_val = ((t_env*)tmp->content)->value;
	if (isatty(0))
	{
		ft_putstr_fd(env_val, STDERR_FILENO);
		ft_putstr_fd("$> ", STDERR_FILENO);
	}
}
