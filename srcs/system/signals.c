#include "minishell.h"

void	signal_handling_register(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sigint_handler(int signal_value)
{
	g_global.last_return = 130;
	if (process_is_parent() == PARENT_PID)
	{
		kill(g_global.pid, signal_value);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (process_is_parent() == CHILD_PID)
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
