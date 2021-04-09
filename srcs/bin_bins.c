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
			free(path);
		i++;
	}
	if (ret_stat == 0)
		return (path);
	else
		return (NULL);
}

/*
** TODO:
** check getenv return value (if null no match)
** check ft_split return value (if null bad malloc)
** check which_bin_fld return value (if null not found)
*/

int		exec_from_bins(char **cmd, char **envp)
{
	char			*path;
	char			**bin_paths;

	errno = 0;
	path = getenv("PATH");
	bin_paths = ft_split(path, ':');
	path = which_bin_fld(cmd[0], bin_paths);
	free_split(bin_paths);
	if (path)
	{
		exec_bin(path, cmd, envp);
		free(path);
	}
	return (0);
}
