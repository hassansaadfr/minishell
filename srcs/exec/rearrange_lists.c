#include "minishell.h"

void	ft_lstdeltoken(t_list **elem, void (*del)(void *))
{
	t_list	*tmp;

	if (*elem == NULL)
		return ;
	tmp = *elem;
	if ((*elem)->previous == NULL && (*elem)->next == NULL)
		*elem = NULL;
	else if ((*elem)->previous == NULL && (*elem)->next != NULL)
	{
		*elem = (*elem)->next;
		(*elem)->previous = NULL;
	}
	else if ((*elem)->previous != NULL && (*elem)->next == NULL)
		(*elem)->previous->next = NULL;
	else if ((*elem)->previous != NULL && (*elem)->next != NULL)
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
	}
	if (del)
	{
		del(tmp->content);
		ft_free_ptr((void**)&tmp);
	}
}


void	del_and_change_list(t_list **redirs, t_list **to_rm)
{
    (*to_rm)->next = NULL;
    (*to_rm)->previous = NULL;
    ft_lstadd_back(redirs, *to_rm);
}

void	del_smc_node(t_list *tmp)
{
    tmp->previous = NULL;
    tmp->next = NULL;
    ft_lstdeltoken(&tmp, free_token);
}

t_list	*isolate_redirs(t_list **args)
{
	t_list  *redirs;
	t_list  *tmp;
	t_list  *to_rm;

	redirs = NULL;
	while (*args && is_redir_or_fd(*args))
	{
		tmp = *args;
		*args = (*args)->next;
		del_and_change_list(&redirs, &tmp);
	}
	tmp = *args;
	while (tmp)
	{
		to_rm = tmp;
		tmp = tmp->next;
		if (is_redir_or_fd(to_rm))
		{
			ft_lstdeltoken(&to_rm, NULL);
			del_and_change_list(&redirs, &to_rm);
		}
	}
	return (redirs);
}

t_list	*isolate_indpdt_cmd(t_list **tokens)
{
	t_list  *cmd;
	t_list  *tmp;

	cmd = *tokens;
	tmp = *tokens;
	while (tmp)
	{
		if (((t_token*)tmp->content)->type == S_COLON)
		{
			tmp->previous->next = NULL;
			cmd = *tokens;
			*tokens = tmp->next;
			del_smc_node(tmp);
			return (cmd);
		}
		if (tmp->next == NULL)
		{
			*tokens = NULL;
			return (cmd);
		}
		tmp = tmp->next;
	}
	return (cmd);
}
