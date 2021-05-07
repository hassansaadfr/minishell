#include "minishell.h"

void	dbg_display_stat_buff(struct stat stat_buff)
{
	printf("stat_buff.st_mode : %u\n\n", stat_buff.st_mode);
}

void	display_tokens(t_list *tokens)
{
	int		i;
	t_token	*token;
	size_t	len;

	i = 0;
	printf("i\tstr\t\t\t\tlen\t\ttype\n");
	printf("____________________________________________________________\n");
	while (tokens)
	{
		token = tokens->content;
		len = ft_strlen(token->arg);
		printf("%d\t\"%-20.20s\"\t\t%zu\t\t%s\n", i++, token->arg, len,
				enum_to_str(token->type));
		tokens = tokens->next;
	}
	printf("\n");
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
