#include "minishell.h"

int	builtin_pwd(char **argv, t_list *env_list)
{
	char	buff[PATH_MAX];

	(void)env_list;
	(void)argv;
	if (getcwd(buff, PATH_MAX) != NULL)
	{
		ft_putendl_fd(buff, STDOUT_FILENO);
		return (0);
	}
	return (1);
}
