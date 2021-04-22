#include "minishell.h"

void	signals(void)
{
	signal(SIGINT, signal_handler);
}

int		minishell(void)
{
	char	*line;
	int		ret_gnl;

	ret_gnl = 1;
	line = NULL;
	signals();
	while (ret_gnl > 0)
	{
		prompt(global.env_list);
		ret_gnl = get_next_line(STDIN_FILENO, &line);
		if (*line)
			exec(parse(line), global.env_list);
		free(line);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_termios	orig_termios;
	(void)argc;
	(void)argv;

	orig_termios = enable_raw_mode();	

	global.env_list = init_env(envp);
	minishell();
	free_env(&global.env_list);

	disable_raw_mode(orig_termios);
	return (0);
}
