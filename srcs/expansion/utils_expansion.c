#include "minishell.h"

int	token_is(int wanted_type, t_token *token)
{
	return (token->type == wanted_type);
}

void	*arg_contains(char wanted_char, char *arg)
{
	return (ft_strchr(arg, wanted_char));
}

int	token_has_empty_arg(t_token *token)
{
	return (*(token->arg) == '\0');
}

void	advance_list_beginning_if_empty(t_list **args)
{
	t_list	*tmp;

	while (*args && token_has_empty_arg((*args)->content))
	{
		tmp = *args;
		*args = (*args)->next;
		free_token(tmp->content);
		ft_free_ptr((void **)&tmp);
	}
}

void	remove_empty_tokens(t_list **args)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*lst;

	advance_list_beginning_if_empty(args);
	lst = *args;
	while (lst)
	{
		tmp = lst;
		if (token_has_empty_arg(lst->content))
		{
			tmp = lst;
			prev->next = lst->next;
			lst = lst->next;
			free_token(tmp->content);
			ft_free_ptr((void **)&tmp);
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
}
