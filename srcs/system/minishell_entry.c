#include "minishell.h"

int	minishell(t_list *env_list)
{
	if (isatty(STDIN_FILENO))
		return (minishell_tty(env_list));
	else
		return (minishell_non_tty(env_list));
}

int	minishell_init(struct termios *orig_termios,
			t_list *env_list)
{
	*orig_termios = enable_raw_mode();
	if (init_termcaps(env_list) == 0)
	{
		disable_raw_mode(*orig_termios);
		return (1);
	}
	signal_handling_register();
	return (0);
}

int	minishell_tty(t_list *env_list)
{
	int				stop;
	t_list			*history;
	t_input			buff;
	struct termios	orig_termios;
	t_list			*tokens;

	if (minishell_init(&orig_termios, env_list) == 1)
		return (-1);
	init_buff_and_history(&buff, &history);
	stop = 0;
	while (stop == 0)
	{
		prompt();
		tokens = NULL;
		stop = write_buffer(&stop, &buff, history);
		if (stop == 0 && not_empty(buff.buffer))
		{
			stop = add_to_history(&buff, &history);
			tokens = parsing(buff.buffer);
		}
		disable_raw_mode(orig_termios);
		if (tokens != NULL)
			g_global.last_return = executing(tokens, env_list, history);
		orig_termios = enable_raw_mode();
	}
	disable_raw_mode(orig_termios);
	ft_free_ptr((void **)&buff.buffer);
	ft_free_ptr((void **)&buff.backup);
	return (stop);
}

int	minishell_non_tty(t_list *env_list)
{
	int		ret_gnl;
	char	*line;
	t_list	*tokens;

	line = NULL;
	ret_gnl = 1;
	signal_handling_register();
	while (ret_gnl > 0)
	{
		ret_gnl = get_next_line(STDIN_FILENO, &line);
		if (*line)
		{
			tokens = parsing(line);
			executing(tokens, env_list, NULL);
		}
		ft_free_ptr((void **)&line);
	}
	return (0);
}
