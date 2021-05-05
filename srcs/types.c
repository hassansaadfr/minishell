#include "minishell.h"

int		type_metachars(t_token *last_token)
{
	int	type;

	if ((last_token && last_token->type == S_COLON) || last_token == NULL)
		return (ERR_TYPE);
	type = S_COLON;
	return (type);
}

int		find_token_type(t_parse *p)
{
	enum e_types    type;
	t_token         *last_token;

	type = ARG;
	last_token = NULL;
	if (p->tokens)
		last_token = ft_lstlast(p->tokens)->content;
	if (ft_strncmp(p->buffer_start, ";", ft_strlen(p->buffer_start)) == 0)
		type = type_metachars(last_token);
	return (type);
}
