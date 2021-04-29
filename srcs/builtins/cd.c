#include "minishell.h"

static int	update_pwd(t_list *env_list)
{
	char	buff[PATH_MAX];
	char	*final_path;
	int		done;

	done = -1;
	if (getcwd(buff, PATH_MAX) != NULL)
	{
		final_path = ft_strjoin("PWD=", buff);
		done = new_env(env_list, final_path);
		if (!done)
			done = edit_env(env_list, final_path);
		free(final_path);
		return (done);
	}
	return (0);
}

static int	set_old_pwd(char *old_pwd, t_list *env_list)
{
	char	*joined;

	errno = 0;
	joined = NULL;
	joined = ft_strjoin("OLDPWD=", old_pwd);
	if (!joined || errno != 0)
		return (1);
	edit_env(env_list, joined);
	free(joined);
	return (0);
}

static char	*get_path_env(t_list *env_list, char *name)
{
	t_list	*tmp;
	char	*path;

	path = NULL;
	tmp = get_env(env_list, name);
	if (tmp)
		path = ((t_env*)(tmp->content))->value;
	return (path);
}

static char	*get_path(t_list *env_list, char **argv)
{
	char	*path;

	path = NULL;
	if (argv[1])
	{
		if (ft_strncmp(argv[1], "-", ft_strlen(argv[1])) == 0)
			path = get_path_env(env_list, "OLDPWD");
		else
			path = argv[1];
	}
	else
		path = get_path_env(env_list, "HOME");
	return (path);
}

int			builtin_cd(char **argv, t_list *env_list)
{
	int		ret;
	char	old_pwd[PATH_MAX];
	char	*path;

	errno = 0;
	ret = 0;
	path = get_path(env_list, argv);
	if (path)
	{
		getcwd(old_pwd, PATH_MAX);
		ret = chdir(path);
		if (get_strarr_size(argv) > 2)
			errno = E2BIG;
		if (ret == 0 && errno == 0)
		{
			if (update_pwd(env_list))
				return (!set_old_pwd(old_pwd, env_list));
			return (0);
		}
		handle_errno(errno, "cd", argv[1]);
	}
	return (ret);
}
