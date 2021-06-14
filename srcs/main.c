#include "minishell.h"

static int	open_file(char *path)
{
	int	fd;

	fd = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_err(path, NULL, strerror(errno));
		ft_exit_free(126);
	}
	return (fd);
}

static int	minishell_exec_script(t_list *env_list, char *path)
{
	int		ret_gnl;
	char	*line;
	t_list	*tokens;
	int		fd;

	fd = open_file(path);
	line = NULL;
	ret_gnl = 1;
	signal_handling_register();
	while (ret_gnl > 0)
	{
		ret_gnl = get_next_line(fd, &line);
		if (*line)
		{
			if (ft_strncmp(line, "#!", 2) != 0)
			{
				tokens = parsing(line);
				executing(tokens, env_list, NULL);
			}
		}
		ft_free_ptr((void **)&line);
	}
	close(fd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_global.env_list = init_env(envp);
	if (argc > 1)
		g_global.last_return = g_global.env_list, argv[1];
	else
		minishell(g_global.env_list);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_exit_free(g_global.last_return);
	return (0);
}
