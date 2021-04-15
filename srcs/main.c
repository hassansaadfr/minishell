#include "minishell.h"

void	signals(void)
{
	signal(SIGINT, signal_handler);
}

int		minishell(t_list *env_list)
{
    char    *line;
    int     ret_gnl;

    ret_gnl = 1;
    line = NULL;
	signals();
    while (ret_gnl > 0)
    {
        prompt(env_list);
        ret_gnl = get_next_line(0, &line);
        if (*line)
            exec(parse(line), env_list);
        free(line);
    }
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	global.env_list = init_env(envp);
	minishell(global.env_list);
	free_env(&global.env_list);
	return (0);
}
