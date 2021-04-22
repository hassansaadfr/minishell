#include "minishell.h"

void signal_handler(int signal_value)
{
	if (signal_value == SIGINT)
	{
		write(STDOUT_FILENO, "\r\n", 1);
		if (global.pid)
			kill(global.pid, SIGINT);
	//	else
	//		return (0); // NOTHING TO KILL, re-prompt()

		//	prompt(global.env_list);
	}
	//return (1);
}
