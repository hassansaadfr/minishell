#include "minishell.h"

int		token_is(int wanted_type, t_token *token)
{
	return (token->type == wanted_type);
}

void	*arg_contains(char wanted_char, char *arg)
{
	return (ft_strchr(arg, wanted_char));
}
