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

int			builtin_cd(char **argv, t_list *env_list)
{
	int		ret;
	char	old_pwd[PATH_MAX];

	errno = 0;
	ret = 0;
	if (argv[1] && ft_strlen(argv[1]) > 0)
	{
		getcwd(old_pwd, PATH_MAX);
		ret = chdir(argv[1]);
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
