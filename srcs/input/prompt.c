#include "minishell.h"

void	prompt(void)
{
	char	*env_val;
	t_list	*tmp;

	g_global.buff->pos = NULL;
	*(g_global.buff->buffer) = '\0';
	g_global.buff->i = 0;
	env_val = NULL;
	tmp = get_env(g_global.env_list, "PWD");
	if (tmp)
		env_val = ((t_env *)tmp->content)->value;
	if (isatty(0))
	{
		ft_putstr_fd(env_val, STDERR_FILENO);
		ft_putstr_fd("$> ", STDERR_FILENO);
	}
}
