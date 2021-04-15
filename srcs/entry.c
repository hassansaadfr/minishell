#include "minishell.h"

int		minishell(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret_gnl;
	t_list	*env_list;

	(void)argc;
	(void)argv;
	ret_gnl = 1;
	line = NULL;
	env_list = init_env(envp);
	while (ret_gnl > 0)
	{
		prompt(env_list);
		ret_gnl = get_next_line(0, &line);
		if (*line)
			exec(parse(line), env_list);
		free(line);
	}
	free_env(&env_list);
	return (1);
}
