#include "minishell.h"

void	sigint_handler(int signal_value)
{
	(void)signal_value;
	if (global.pid)
	{
		kill(global.pid, SIGINT);
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		prompt();
	}
}
