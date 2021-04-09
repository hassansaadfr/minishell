#include "minishell.h"

int			builtin_pwd(char **argv, char **env)
{
	(void)argv;
	(void)env;
	printf("%s\n", getenv("PWD"));
	return (1);
}
