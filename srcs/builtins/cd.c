#include "minishell.h"

static int	update_pwd(t_list *env_list)
{
	char	buff[PATH_MAX];
	char	*final_path;

	if (getcwd(buff, PATH_MAX) != NULL)
	{
		final_path = ft_strjoin("PWD=", buff);
		edit_env(env_list, final_path);
		return (1);
	}
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
			{
				edit_env(env_list, ft_strjoin("OLDPWD=", old_pwd));
				return (1);
			}
			return (0);
		}
		handle_errno(errno, "cd", argv[1]);
	}
	return (ret);
}
