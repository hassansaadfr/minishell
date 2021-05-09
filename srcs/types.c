#include "minishell.h"

int		check_exclusions(enum e_types type, t_token *last_token)
{
	if (type == S_COLON &&
			((last_token && last_token->type == S_COLON) || last_token == NULL))
		return (ERR_TYPE);
	return (type);
}

int		is_redir(enum e_types type)
{
	return (type == REDIR_INF || type == REDIR_SUP || type == REDIR_DSUP);
}

int		find_token_type(t_parse *p, size_t token_len, t_token *last_token)
{
	if (last_token && is_redir(last_token->type))
		return (FD);
	else if (ft_strncmp(p->buffer_start, ";", token_len) == 0)
		return (S_COLON);
	else if (ft_strncmp(p->buffer_start, "<", token_len) == 0)
		return (REDIR_INF);
	else if (ft_strncmp(p->buffer_start, ">", token_len) == 0)
		return (REDIR_SUP);
	else if (ft_strncmp(p->buffer_start, ">>", token_len) == 0)
		return (REDIR_DSUP);
	else if (ft_strncmp(p->buffer_start, "|", token_len) == 0)
		return (PIPE);
	else
		return (ARG);
}

int		typing(t_parse *p)
{
	enum e_types	type;
	t_token			*last_token;
	size_t			token_len;

	last_token = NULL;
	token_len = ft_strlen(p->buffer_start);
	if (p->tokens)
		last_token = ft_lstlast(p->tokens)->content;
	type = find_token_type(p, token_len, last_token);
	type = check_exclusions(type, last_token);
	return (type);
}
