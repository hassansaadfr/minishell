#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_global.env_list = init_env(envp);
	init_path_and_shlvl(&g_global.env_list);
	minishell(g_global.env_list);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_exit_free(0);
	return (0);
}
