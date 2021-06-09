#include "minishell.h"

int	minishell(t_list *env_list)
{
	if (isatty(STDIN_FILENO))
		return (minishell_tty(env_list));
	else
		return (minishell_non_tty(env_list));
}

int	minishell_init(struct termios *orig_termios, t_list *env_list)
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
	t_msh	msh;

	if (minishell_init(&msh.orig_termios, env_list) == 1)
		return (-1);
	init_buff_and_history(&msh.buff, &msh.history);
	msh.stop = 0;
	while (msh.stop == 0)
	{
		prompt();
		msh.tokens = NULL;
		msh.stop = write_buffer(&msh.stop, &msh.buff, msh.history);
		if (msh.stop == 0 && not_empty(msh.buff.buffer))
		{
			msh.stop = add_to_history(&msh.buff, &msh.history);
			msh.tokens = parsing(msh.buff.buffer);
		}
		disable_raw_mode(msh.orig_termios);
		if (msh.tokens != NULL)
			g_global.last_return = executing(msh.tokens, env_list, msh.history);
		msh.orig_termios = enable_raw_mode();
	}
	disable_raw_mode(msh.orig_termios);
	ft_free_ptr((void **)&msh.buff.buffer);
	ft_free_ptr((void **)&msh.buff.backup);
	return (msh.stop);
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
