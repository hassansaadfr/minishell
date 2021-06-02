#include "minishell.h"

void	sigint_handler(int signal_value)
{
	if (process_is_parent() == PARENT_PID)
	{
		kill(g_global.pid, signal_value);
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		prompt();
	}
}

void	sigquit_handler(int signal_value)
{
	if (process_is_parent() == PARENT_PID)
	{
		ft_putstr_fd("Quitter (core dumped)\n", STDERR_FILENO);
		kill(g_global.pid, signal_value);
	}
}
