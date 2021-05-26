#include "minishell.h"

/*
** TODO:
** check create_full_path return value
** check stat return value
** if ret_stat != 0 set errno
*/

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

int		exec_from_bins(char **cmd, t_list *env_list/*, t_termios orig_termios*/)
{
	t_list			*env_node;
	char			*path;
	char			**bin_paths;

	errno = 0;
	env_node = get_env(env_list, "PATH");
	if (env_node)
	{
		path = ((t_env*)env_node->content)->value;
		bin_paths = ft_split(path, ':');
		path = which_bin_fld(cmd[0], bin_paths);
		free_split(bin_paths);
		if (path)
		{
			exec_bin(path, cmd, env_list);
			ft_free_ptr((void**)&path);
		}
	}
	return (0);
}

/*
** TODO:
** - Check strjoin returns
*/

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

// int		search_bin(char *cmd, t_list *env_list)
// {
// 	char	*path_env;
// 	char	*path;
// 	char	**bin_paths;

// 	path_env = get_env_value(env_list, "path");
// 	if (path_env)
// 	{
// 		bin_paths = ft_split(path_env, ':');
// 		path = which_bin_fld(cmd, bin_paths);
// 		free_split(bin_paths);
// 		ft_free_ptr((void**)&path_env);
// 	}
// 	return (0);
// }

/*
** waitpid() return -1 on error
** pid > 0 = parent
** pid == 0 = child
*/

int			exec_bin(char *path, char **args, t_list *env_list)
{
	int		ret;
	int		status;
	char	**env;

	errno = 0;
	g_global.pid = fork();
	env = NULL;
	if (g_global.pid > 0)
	{
		ret = waitpid(0, &status, 0);
		g_global.pid = 0;
	}
	else if (g_global.pid == 0)
	{
		env = list_to_array(env_list);
		ret = execve(path, args, env);
	}
	else
		printf("ERROR - fork\n");
	return (0);
}

static char	*get_path(char *cmd, t_list *env_list)
{
	char	*path;

	path = NULL;
	if (is_path(cmd))
		path = create_full_path(get_env_value(env_list, "PWD"), cmd);
	else if (ft_strcmp("./", cmd))
		return (cmd);
	return (path);
}

static int	search_bin(char **cmd, t_list *env_list, t_list *history)
{
	int	ret_exec;
	char *path;

	ret_exec = 0;
	if (is_builtin(cmd))
		ret_exec = exec_from_builtins(cmd, env_list, history);
	else
	{
		path = get_path(cmd[0], env_list); // cree un path si c'est un path ou si c'est dans les dossiers de binaires
		// ret_stat = stat(path);
	}
	/*
	else if (is_path(cmd[0]))
		ret_exec = exec_from_path(cmd, env_list);
	else
		ret_exec = exec_from_bins(cmd, env_list);
	if (ret_exec != 0 || ret_exec == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putstr_fd(*cmd, STDERR_FILENO);
	}
	*/
	return (ret_exec);
}

int			execution(char ***cmds, t_list *env_list, t_list *history)
{
	int		i;

	i = 0;
	while (cmds[i])
		search_bin(cmds[i++], env_list, history);
	free_cmds(cmds);
	return (0);
}
