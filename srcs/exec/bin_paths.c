#include "minishell.h"

// int			is_path(char *cmd)
// {
// 	char	*slash_pos;

// 	slash_pos = ft_strchr(cmd, '/');
// 	if (slash_pos)
// 		return (1);
// 	return (0);
// }

/*
** TODO:
** Should control return of checked_path in elseif
*/

int			exec_from_path(char **cmd, t_list *env_list/*, t_termios orig_termios*/)
{
	int				ret_stat;
	char			*checked_path;
	struct stat		stat_buff;

	ret_stat = -1;
	errno = 0;
	if (ft_strncmp(cmd[0], "./", 2) == 0)
		checked_path = create_full_path(get_env_value(env_list, "PWD"), cmd[0] + 2);
	else if (ft_strncmp(cmd[0], "/", 1) == 0)
	{
		checked_path = ft_strdup(cmd[0]);
	}
	else
		checked_path = create_full_path(get_env_value(env_list, "PWD"), cmd[0]);
	ret_stat = stat(checked_path, &stat_buff);
	if (ret_stat == 0)
		exec_bin(checked_path, cmd, env_list);
	ft_free_ptr((void**)&checked_path);
	return (ret_stat);
}
