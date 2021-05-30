#include "minishell.h"

static int	process_is_parent(void)
{
	if (g_global.pid > 0)
		return (PARENT_PID);
	else if (g_global.pid == 0)
		return (CHILD_PID);
	else
		return (ERROR_FORK);
}

static int	exec_bin(char *path, char **args, t_list *env_list)
{
	int		ret;
	int		status;
	char	**env;
	int		exec_ret;

	errno = 0;
	exec_ret = 0;
	g_global.pid = fork();
	env = NULL;
	if (process_is_parent() == PARENT_PID)
	{
		ret = waitpid(0, &status, 0);
		g_global.pid = 0;
		exec_ret = WEXITSTATUS(status);
	}
	else if (process_is_parent() == CHILD_PID)
	{
		env = list_to_array(env_list);
		exec_ret = execve(path, args, env);
		if (exec_ret == -1)
			exit(125 + errno);
	}
	else
		printf("ERROR - fork\n");
	return (exec_ret);
}

static int	can_exec(char *path)
{
	struct stat		stat_buff;
	int				ret_stat;

	errno = 0;
	ret_stat = stat(path, &stat_buff);
	if ((stat_buff.st_mode & S_IXOTH) == 1)
		return (ret_stat);
	else
	{
		errno = EPERM;
		return (125 + errno);
	}
}

static int	search_bin(char **cmd, t_list *env_list)
{
	char	*path;
	char	*lang;

	lang = NULL;
	path = get_binary_path(cmd[0], env_list);
	if (path == NULL)
	{
		lang = get_env_value(env_list, "LANG");
		if (lang && ft_strncmp(lang, "fr_FR", 4) == 0)
			print_err(NULL, cmd[0], COMMAND_NOT_FOUND_FR);
		else
			print_err(NULL, cmd[0], COMMAND_NOT_FOUND_EN);
		return (-1);
	}
	else
	{
		ft_free_ptr((void**)&cmd[0]);
		cmd[0] = path;
		return (can_exec(path));
	}
}

int			execution(char **cmds, t_list *env_list, t_list *history)
{
	int		can_exec;
	int		return_value;

	return_value = 0;
	if (is_builtin(cmds))
		return (exec_from_builtins(cmds, env_list, history));
	else
	{
		can_exec = search_bin(cmds, env_list);
		if (can_exec == 0)
		{
			return_value = exec_bin(cmds[0], cmds, env_list);
			if (return_value >= 125)
				return (return_value);
		}
		else if (can_exec > 125)
			print_err(NULL, cmds[0], strerror(can_exec - 125));
		return (return_value);
	}
}
