#include "minishell.h"

int		token_is(int wanted_type, t_token *token)
{
	return (token->type == wanted_type);
}

void	*arg_contains(char wanted_char, char *arg)
{
	return (ft_strchr(arg, wanted_char));
}

int		token_has_empty_arg(t_token *token)
{
	return (*(token->arg) == '\0');
}
