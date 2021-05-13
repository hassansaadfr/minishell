#include "minishell.h"

void		signal_handling_register(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
** TODO:
** -	SHOULD REMOVE orig_termios FROM exec() FUNCTIONS
** 		THEN SHOULD ACTIVATE NON-CANONICAL MODE BEFORE write_buffer()
** 		AND THEN SHOULD DEACTIVATE NON-CANONICAL MODE AFTER
** -	SHOULD signal_handling_register() IN main() FCUNTION
*/

//static int	minishell_tty(t_termios orig_termios)
static int	minishell_tty(void)
{
	int			stop;
	t_list		*history;
	t_input		buff;
	t_termios	orig_termios;

	orig_termios = enable_raw_mode();
	if (init_termcaps(g_global.env_list) == 0)
	{
		disable_raw_mode(orig_termios);
		return (-1);
	}
	signal_handling_register();
	init_buff_and_history(&buff, &history);
	stop = 0;
	while (stop == 0)
	{
		prompt();
		stop = write_buffer(&stop, &buff, history);
		disable_raw_mode(orig_termios);
		if (stop == 0)
			stop = add_to_history(&buff, &history);
		if (stop == 0)
			execution(parse(buff.buffer), g_global.env_list/*, orig_termios*/, history);
		orig_termios = enable_raw_mode();
	}
	ft_lstclear(&history, free);
	free(buff.buffer);
	free(buff.backup);
	return (stop);
}

//static int	minishell_non_tty(t_termios orig_termios)
static int	minishell_non_tty(void)
{
	int		ret_gnl;
	char	*line;
	char	***cmds;

	line = NULL;
	ret_gnl = 1;
	signal_handling_register();
	while (ret_gnl > 0)
	{
		ret_gnl = get_next_line(STDIN_FILENO, &line);
		if (*line)
		{
			cmds = parse(line);
			execution(cmds, g_global.env_list/*, orig_termios*/, NULL);
		}
		free(line);
	}
	return (0);
}

//int			minishell(t_termios orig_termios)
int			minishell(void)
{
	if (isatty(STDIN_FILENO))
//		return (minishell_tty(orig_termios));
		return (minishell_tty());
	else
//		return (minishell_non_tty(orig_termios));
		return (minishell_non_tty());
}

int			main(int argc, char **argv, char **envp)
{
//	t_termios	orig_termios;

	(void)argc;
	(void)argv;
	g_global.env_list = init_env(envp);
	/*
	orig_termios = enable_raw_mode();
	if (init_termcaps(g_global.env_list) == 0)
	{
		disable_raw_mode(orig_termios);
		return (-1);
	}
	*/
//	minishell(orig_termios);
	minishell();
	free_env(&g_global.env_list);
//	disable_raw_mode(orig_termios);
	return (0);
}
