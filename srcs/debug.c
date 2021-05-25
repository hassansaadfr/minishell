#include "minishell.h"

void	dbg_display_stat_buff(struct stat stat_buff)
{
	printf("stat_buff.st_mode : %u\n\n", stat_buff.st_mode);
}

void	print_token_arg(t_token *token)
{
	int	j;

	j = 0;
	while (token->arg[j] && j < 40)
	{
		if (token->arg[j] > 0)
			printf("%c", token->arg[j]);
		else
		{
			printf("\033[1;31m");
			printf("%c", -token->arg[j]);
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

void	display_tokens(t_list *tokens)
{
	int		i;
	t_token	*token;
	size_t	len;

	i = 0;
	printf("i\tstr\t\t\t\t\t\t\tlen\t\ttype\n");
	printf("__________________________________________________________________________________________\n");
	while (tokens)
	{
		token = tokens->content;
		len = ft_strlen(token->arg);
		printf("%d\t\"", i++);
		print_token_arg(token);
		printf("\"\t\t%zu\t\t%s\n", len, enum_to_str(token->type));
		tokens = tokens->next;
	}
	printf("\n");
}

void    display_splitted_cmd(t_list *cmd, int debug_i, char *type)
{
	if (ft_strncmp(type, "CMD", 4) == 0)
	{
		printf("\t============================================================\n");
		printf("\t========================== %3.3s %2i ==========================\n",
				type, debug_i++);
	}
	else
	printf("========================== %3.3s %2i ==========================\n",
			type, debug_i++);
	if (ft_strncmp(type, "CMD", 4) == 0)
		printf("\t============================================================\n");
	display_tokens(cmd);
}

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
