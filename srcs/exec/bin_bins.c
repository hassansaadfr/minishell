#include "minishell.h"

/*
** TODO:
** check getenv return value (if null no match)
** check ft_split return value (if null bad malloc)
** check which_bin_fld return value (if null not found)
*/

// int		exec_from_bins(char **cmd, t_list *env_list/*, t_termios orig_termios*/)
// {
// 	t_list			*env_node;
// 	char			*path;
// 	char			**bin_paths;

// 	errno = 0;
// 	env_node = get_env(env_list, "PATH");
// 	if (env_node)
// 	{
// 		path = ((t_env*)env_node->content)->value;
// 		bin_paths = ft_split(path, ':');
// 		path = which_bin_fld(cmd[0], bin_paths);
// 		free_split(bin_paths);
// 		if (path)
// 		{
// 			exec_bin(path, cmd, env_list);
// 			ft_free_ptr((void**)&path);
// 		}
// 	}
// 	return (0);
// }
