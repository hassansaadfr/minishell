#include "minishell.h"

char	*enum_to_str(int type)
{
	if (type == ARG)
		return ("ARG");
	else if (type == REDIR_INF)
		return ("REDIR_INF");
	else if (type == REDIR_SUP)
		return ("REDIR_SUP");
	else if (type == REDIR_DSUP)
		return ("REDIR_DSUP");
	else if (type == FD)
		return ("FILE");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == S_COLON)
		return ("S_COLON");
	return ("ERR STATE");
}

void	print_token_str(char *arg)
{
	int	j;

	j = 0;
	while (arg[j] && j < 40)
	{
		if (arg[j] > 0)
			printf("%c", arg[j]);
		else
		{
			printf("\033[1;31m");
			printf("%c", -arg[j]);
			printf("\033[0m");
		}
		j++;
	}
	while (j < 40)
	{
		printf(" ");
		j++;
	}
}
