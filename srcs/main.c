#include "minishell.h"

//void	signals(t_buff *buff)
void	signals(void)
{
//	sighandler_t	ret_signal;

//	ret_signal = signal(SIGINT, signal_handler);
	signal(SIGINT, signal_handler);

	//if (ret_signal == 0)
	//	prompt(global.env_list, buff);
}

int		minishell(void)
{
	int		stop;
	t_list	*history;
	t_buff	buff;

	signals();
	init_buff_and_history(&buff, &history);
	stop = 0;
	while (stop == 0)
	{
		prompt(global.env_list, &buff);
		stop = write_buffer(&stop, &buff, history);
		if (stop == 0)
		{
			stop = add_to_history(&buff, &history);
			if (stop == 0)
				exec(parse(buff.buffer), global.env_list);
		}
	}
	ft_lstclear(&history, free);
	free(buff.buffer);
	free(buff.backup);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_termios	orig_termios;
	(void)argc;
	(void)argv;

	orig_termios = enable_raw_mode();
	if (init_termcaps() == 0)
	{
		disable_raw_mode(orig_termios);
		return (-1);
	}

	global.env_list = init_env(envp);
	minishell();
	free_env(&global.env_list);

	disable_raw_mode(orig_termios);
	return (0);
}
