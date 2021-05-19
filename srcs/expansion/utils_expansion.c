#include "minishell.h"

int		token_is(enum e_types wanted_type, t_token *token)
{
	return (token->type == wanted_type);
}

int		token_arg_contains(char wanted_char, char *arg)
{
	return (ft_strchr(arg, wanted_char));
}
