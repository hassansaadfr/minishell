#include "minishell.h"

t_path	get_path_type(char *str)
{
	t_path	type;

	type = NO_PATH;
	if (str[0] == '/')
		return (ABSOLUTE_PATH);
	else
	{
		if (ft_strchr(str, '/'))
			return (RELATIVE_PATH);
	}
	return (type);
}

static char		*create_full_path(char *bin_path, char *cmd)
{
	char	*tmp;
	char	*s;

	s = ft_strjoin(bin_path, "/");
	tmp = s;
	s = ft_strjoin(s, cmd);
	ft_free_ptr((void**)&tmp);
	return (s);
}

static char		*which_bin_fld(char *bin, char **bin_paths)
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

static char		*find_bin_in_path(char *bin, t_list *env_list)
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

char			*get_binary_path(char *cmd, t_list *env_list)
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
