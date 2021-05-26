#include "minishell.h"

char	*which_bin_fld(char *bin, char **bin_paths)
{
	char			*path;
	int				i;
	struct stat		stat_buff;
	int				ret_stat;

	errno = 0;
	i = 0;
	ret_stat = -1;
	while (bin_paths[i] && ret_stat != 0)
	{
		path = create_full_path(bin_paths[i], bin);
		ret_stat = stat(path, &stat_buff);
		if (ret_stat)
			ft_free_ptr((void**)&path);
		i++;
	}
	if (ret_stat == 0)
		return (path);
	else
		return (NULL);
}

static char	*find_bin_in_path(char *bin, t_list *env_list)
{
	char			*path;
	char			*path_var_env;
	char			**path_list;

	path = NULL;
	path_var_env = get_env_value(env_list, "PATH");
	if (path_var_env)
	{
		path_list = ft_split(path_var_env, ':');
		path = which_bin_fld(bin, path_list);
		free_split(path_list);
	}
	return (path);
}

char		*create_full_path(char *bin_path, char *cmd)
{
	char	*tmp;
	char	*s;

	s = ft_strjoin(bin_path, "/");
	tmp = s;
	s = ft_strjoin(s, cmd);
	ft_free_ptr((void**)&tmp);
	return (s);
}

int			exec_bin(char *path, char **args, t_list *env_list)
{
	int		ret;
	int		status;
	char	**env;
	int		exec_ret;

	errno = 0;
	exec_ret = 0;
	g_global.pid = fork();
	env = NULL;
	if (g_global.pid > 0)
	{
		ret = waitpid(0, &status, 0);
		g_global.pid = 0;
		exec_ret = WEXITSTATUS(status);
	}
	else if (g_global.pid == CHILD_PID)
	{
		env = list_to_array(env_list);
		exec_ret = execve(path, args, env);
		if (exec_ret == -1)
			return (125 + errno);
	}
	else
		printf("ERROR - fork\n");
	return (exec_ret);
}

static char	*get_path(char *cmd, t_list *env_list)
{
	char				*path;
	t_path				path_type;
	char				*pwd;

	pwd = get_env_value(env_list, "PWD");
	path_type = get_path_type(cmd);
	path = NULL;
	if (path_type == NO_PATH)
		path = find_bin_in_path(cmd, env_list);
	else if (path_type == RELATIVE_PATH)
		path = create_full_path(pwd, cmd);
	else
		path = cmd;
	return (path);
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

static int	search_bin(char **cmd, t_list *env_list, t_list *history)
{
	char	*path;
	char	*lang;

	lang = NULL;
	if (is_builtin(cmd))
		return (exec_from_builtins(cmd, env_list, history));
	else
	{
		path = get_path(cmd[0], env_list);
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
}

int			execution(char **cmds, t_list *env_list, t_list *history)
{
	int		can_exec;
	int		return_value;

	return_value = 0;
	can_exec = search_bin(cmds, env_list, history);
	if (can_exec == 0)
		return_value = exec_bin(cmds[0], cmds, env_list);
	else if (can_exec > 125)
		print_err(NULL, cmds[0], strerror(can_exec - 125));
	return (return_value);
}
