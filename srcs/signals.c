#include "minishell.h"

void	signal_handler(int signal_value)
{
	if (signal_value == SIGINT)
	{
		write(1, "\n", 1);
		if (global.pid)
			kill(global.pid, SIGINT);
		else
			prompt(global.env_list);
	}
}
