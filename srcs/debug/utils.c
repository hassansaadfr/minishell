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

void	display_token_to_be_splitted(t_token *token, char **arg_split)
{
	int	i;

	printf("========================== SPL  0 ==========================\n");
	printf("TOKEN : \"%40s\"\n", token->arg);
	printf("MUST BE SPLITTED AS :\n");
	i = 0;
	while (arg_split[i])
	{
		printf("\t%2d\t\"", i);
		print_token_str(arg_split[i]);
		printf("\"\n");
		i++;
	}
	printf("\n");
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
