#include "minishell.h"

int		smc_exclusions(t_token *last_token)
{
	int		last_type;

	if (last_token == NULL)
		return (ERR_TYPE);
	else
	{
		last_type = last_token->type;
		if (last_type != ARG && last_type != FD)
			return (ERR_TYPE);
	}
	return (S_COLON);
}

int		pipe_exclusions(t_token *last_token)
{
	int		last_type;

	if (last_token == NULL)
		return (ERR_TYPE);
	else
	{
		last_type = last_token->type;
		if (last_type != ARG && last_type != FD)
			return (ERR_TYPE);
	}
	return (PIPE);
}

int		redirs_exclusions(t_token *last_token, int curr_type)
{
	int		last_type;

	last_type = 0;
	if (last_token)
		last_type = last_token->type;
	if (last_type && is_redir(last_type))
		return (ERR_TYPE);
	return (curr_type);
}

int		newline_exclusions(t_list *last_node)
{
	int		last_type;
	t_token	*last_token;

	last_type = 0;
	last_token = NULL;
	if (last_node)
		last_token = last_node->content;
	if (last_token == NULL)
		return (1);
	else
		last_type = last_token->type;
	if (last_type &&
			(last_type == S_COLON || last_type == FD || last_type == ARG))
		return (1);
	return (0);
}
