#include "minishell.h"

void	signal_handling_register(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int		minishell(t_termios orig_termios)
{
	int		stop;
	t_list	*history;
	t_buff	buff;
	int		ret_gnl;
	char	*line;

	signal_handling_register();
	init_buff_and_history(&buff, &history);
	stop = 0;
	line = NULL;
	ret_gnl = 1;
	if (isatty(STDIN_FILENO))
	{
		while (stop == 0)
		{
			// ENABLE RAW_MODE ICI
			prompt();
			stop = write_buffer(&stop, &buff, history);
			// DISBLE RAW_MODE ICI
			if (stop == 0)
			{
				stop = add_to_history(&buff, &history);
				if (stop == 0)
					exec(parse(buff.buffer), global.env_list, orig_termios);
			}
		}
	}
	else
	{
		while (ret_gnl > 0)
		{
			prompt();
			ret_gnl = get_next_line(0, &line);
			if (*line)
				exec(parse(line), global.env_list, orig_termios);
			free(line);
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
	minishell(orig_termios);
	free_env(&global.env_list);

	disable_raw_mode(orig_termios);
	return (0);
}
