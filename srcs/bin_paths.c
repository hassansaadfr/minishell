#include "minishell.h"

int		 is_path(char *cmd)
{
	char	*slash_pos;

	slash_pos = ft_strchr(cmd, '/');
	if (slash_pos)
		return (1);
	return (0);
}

int		exec_from_path(char **cmd, char **envp)
{
	int				ret_stat;
	char			*checked_path;
	struct stat		stat_buff;

	ret_stat = -1;
	errno = 0;
	if (ft_strncmp(cmd[0], "./", 2) == 0)
		checked_path = create_full_path(getenv("PWD"), cmd[0] + 2);
	else if (ft_strncmp(cmd[0], "/", 1) == 0)
		checked_path = cmd[0];
	else
		checked_path = create_full_path(getenv("PWD"), cmd[0]);
	ret_stat = stat(checked_path, &stat_buff);
	//printf("EXECUTING\t=\t\"%s\"\nRET_STAT\t=\t%d\n", checked_path, ret_stat);
	if (ret_stat == 0)
		exec_bin(checked_path, cmd, envp);
	//ELSE
	free(checked_path);
	return (0);
}
