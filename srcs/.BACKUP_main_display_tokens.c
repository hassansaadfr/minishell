#include "minishell.h"

void		signal_handling_register(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
** TODO:
** SHOULD REMOVE orig_termios FROM exec() FUNCTIONS
** THEN SHOULD ACTIVATE NON-CANONICAL MODE BEFORE write_buffer()
** AND THEN SHOULD DEACTIVATE NON-CANONICAL MODE AFTER
*/

static int	minishell_tty(void)
{
	int		stop;
	t_list	*history;
	t_input	buff;
	t_list	*tokens;

	signal_handling_register();
	init_buff_and_history(&buff, &history);
	stop = 0;
	tokens = NULL;
	while (stop == 0)
	{
		prompt();
		stop = write_buffer(&stop, &buff, history);
		if (stop == 0)
			stop = add_to_history(&buff, &history);
		if (stop == 0 && not_empty(buff.buffer))
			tokens = parsing(buff.buffer);
		if (tokens && DEBUG)
			display_tokens(tokens);
		if (tokens)
			ft_lstclear(&tokens, free_token);
	}
	if (history)
		ft_lstclear(&history, free);
	if (buff.buffer)
		free(buff.buffer);
	if (buff.backup)
		free(buff.backup);
	return (stop);
}

/*
**	ANCIENT EXEC COMMAND : (in place of (void)cmds; (void)orig_termios;
**	cmds = parse(line);
**	exec(cmds, g_global.env_list, orig_termios);
*/

static int	minishell_non_tty(t_termios orig_termios)
{
	int		ret_gnl;
	char	*line;
	char	***cmds;
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
			display_tokens(tokens);
			ft_lstclear(&tokens, free);
			(void)orig_termios;
			(void)cmds;
		}
		free(line);
	}
	return (0);
}

int			minishell(t_termios orig_termios)
{
	if (isatty(STDIN_FILENO))
		return (minishell_tty());
	else
		return (minishell_non_tty(orig_termios));
}

int			main(int argc, char **argv, char **envp)
{
	t_termios	orig_termios;

	(void)argc;
	(void)argv;
	g_global.env_list = init_env(envp);
	orig_termios = enable_raw_mode();
	if (init_termcaps(g_global.env_list) == 0)
	{
		disable_raw_mode(orig_termios);
		return (-1);
	}
	minishell(orig_termios);
	free_env(&g_global.env_list);
	disable_raw_mode(orig_termios);
	return (0);
}