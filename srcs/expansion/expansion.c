#include "minishell.h"

void	expand(t_list **cmd, t_list *env_list)
{	
	char	*dollar_pos;
	t_token	*token;

	token = (*cmd)->content;
	dollar_pos = ft_strchr(token->arg, '$');
}

t_list	*expansion(t_list *cmd, t_list *env_list)
{
	t_list	*list_start;
	t_token	*token;

	list_start = cmd;
	while (cmd)
	{
		token = cmd->content;
		if (token_arg_contains('$', token->arg))
		{
			if (token_is(FD, token))
				expand_in_fd(cmd, env_list);
			else if (token_arg_contains('"', token->arg))
				expand_in_d_quote(cmd, env_list);
			else
				expand(&cmd, env_list);
			remove_escaping(cmd);
			neg_to_pos(cmd);
		}
		cmd = cmd->next;
	}
	return (list_start);
}
