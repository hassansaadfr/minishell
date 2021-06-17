#include "minishell.h"

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
			ft_exit_free(125 + errno);
	}
	else
		return (return_err_msg("fork", strerror(errno), 254));
	return (exec_ret);
}

static int	can_exec(char *path)
{
	struct stat		stat_buff;
	int				ret_stat;

	errno = 0;
	ret_stat = stat(path, &stat_buff);
	if (ret_stat == -1)
		return (127);
	if (!S_ISREG(stat_buff.st_mode))
		return (126);
	if ((stat_buff.st_mode & S_IXOTH) == 1)
		return (ret_stat);
	else
	{
		errno = EPERM;
		return (125 + errno);
	}
}

int	search_bin(char **cmd, t_list *env_list)
{
	char	*path;

	if (ft_strcmp(cmd[0], ".") == 0)
	{
		print_err(NULL, NULL, "nom de fichier nécessaire en argument");
		return (2);
	}
	if (ft_strcmp(cmd[0], "..") == 0)
	{
		return (127);
	}
	path = NULL;
	path = get_binary_path(cmd[0], env_list);
	if (path == NULL)
		return (127);
	else
	{
		ft_free_ptr((void **)&cmd[0]);
		cmd[0] = path;
		return (can_exec(cmd[0]));
	}
}

int	execution(char **cmds, t_list *env_list, t_list *history)
{
	int		can_exec;
	int		return_value;
	char	*arg;

	arg = ft_strdup(*cmds);
	return_value = 0;
	if (is_builtin(cmds))
		return (exec_from_builtins(cmds, env_list, history));
	else
	{
		can_exec = search_bin(cmds, env_list);
		edit_underscore_var(env_list, cmds[get_strarr_size(cmds) - 1]);
		if (can_exec == 0)
			return_value = exec_bin(cmds[0], cmds, env_list);
		else
		{
			return_value = can_exec;
			if (can_exec > 125)
				print_err(NULL, arg, strerror(can_exec - 125));
		}
		ft_free_ptr((void **)&arg);
		return (return_value);
	}
}
