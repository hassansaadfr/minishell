#include "minishell.h"

void	signal_handling_register(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

/*
** TODO:
** -	SHOULD REMOVE orig_termios FROM exec() FUNCTIONS
** 		THEN SHOULD ACTIVATE NON-CANONICAL MODE BEFORE write_buffer()
** 		AND THEN SHOULD DEACTIVATE NON-CANONICAL MODE AFTER
** -	SHOULD signal_handling_register() IN main() FCUNTION
*/

static int	minishell_tty(t_list *env_list)
{
	int			stop;
	t_list		*history;
	t_input		buff;
	t_termios	orig_termios;
	t_list		*tokens;

	g_global.last_return = 42;
	orig_termios = enable_raw_mode();
	if (init_termcaps(env_list) == 0)
	{
		disable_raw_mode(orig_termios);
		return (-1);
	}
	signal_handling_register();
	init_buff_and_history(&buff, &history);
	stop = 0;
	tokens = NULL;
	while (stop == 0)
	{
		prompt();
		tokens = NULL;
		stop = write_buffer(&stop, &buff, history);
		if (stop == 0 && not_empty(buff.buffer))
			stop = add_to_history(&buff, &history);
		if (stop == 0 && not_empty(buff.buffer))
			tokens = parsing(buff.buffer);
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

static int	minishell_non_tty(t_list *env_list)
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

int	minishell(t_list *env_list)
{
	if (isatty(STDIN_FILENO))
		return (minishell_tty(env_list));
	else
		return (minishell_non_tty(env_list));
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_global.env_list = init_env(envp);
	minishell(g_global.env_list);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_exit_free(0);
	return (0);
}
