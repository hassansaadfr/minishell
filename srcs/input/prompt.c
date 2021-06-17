#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr_fd("msh_$> ", STDERR_FILENO);
}

void	prompt(void)
{
	g_global.buff->pos = NULL;
	*(g_global.buff->buffer) = '\0';
	g_global.buff->i = 0;
	if (isatty(0))
		print_prompt();
}
