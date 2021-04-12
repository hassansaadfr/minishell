#include "minishell.h"

int			builtin_pwd(char **argv, t_list *env_list)
{
	char	buff[PATH_MAX];

	(void)env_list;
	(void)argv;
	if (getcwd(buff, PATH_MAX) != NULL)
	{
		printf("%s\n", buff);
		return (1);
	}
	return (0);
}
