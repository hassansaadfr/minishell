#include "minishell.h"

/*
void	expand(t_list **cmd, t_list *env_list)
{	
	char	*dollar_pos;
	char	*arg_start;
	t_token	*token;

	token = (*cmd)->content;
	dollar_pos = ft_strchr(token->arg, '$');
	arg_start = token->arg;
	while (dollar_pos)
	{
		dollar_pos = ft_strchr(token->arg, '$');
	}
}

t_list	*expand_args(t_list *cmd, t_list *env_list)
{
	t_list	*list_start;
	t_token	*token;

	list_start = cmd;
	while (cmd)
	{
		token = cmd->content;
		if (arg_contains('$', token->arg))
		{
			if (token_is(FD, token))
				expand_fd(cmd, env_list);
			else if (arg_contains('"', token->arg))
				expand_d_quote(cmd, env_list);
			expand(&cmd, env_list);
			remove_escaping(cmd);
			neg_to_pos(cmd);
		}
		cmd = cmd->next;
	}
	return (list_start);
}
*/

1 - trouver le '$'
//2 - incrementer le ptr sur la pos ==> on est sur la position de la premiere lettre de la key
3 - trouver le bout de str qui constitue la key
4 - calculer la longueur de la key 
5 - ft_substr la key
6 - expansion = get_env(key)

void	expand_fd(t_token *token, t_list *env_list, char *dollar_pos)
{
	(void)dollar_pos;
	char	*expansion;	
	char	*arg_start;
	t_list	*node;

	expansion = "";
	node = NULL;
	arg_start = token->arg;
	node = get_env(env_list, dollar_pos + 1);
	if (node != NULL && node->content != NULL && ((t_env*)node->content)->value != NULL)
		expansion = ((t_env*)node->content)->value;
	token->arg = expansion;
	ft_free_ptr((void**)&arg_start);
}


t_list	*expand_redirs(t_list **redirs, t_list *env_list)
{
	t_list	*cursor;
	t_token	*token;
	char	*dollar_exists;

	cursor = *redirs;
	dollar_exists = NULL;
	while (cursor)
	{
		token = cursor->content;
		dollar_exists = ft_strchr(token->arg, '$');
		if (token_is(FD, token) && dollar_exists)
			expand_fd(token, env_list, dollar_exists);
		cursor = cursor->next;
	}
	return (*redirs);
}
