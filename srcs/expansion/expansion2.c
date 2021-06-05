#include "minishell.h"

void	expand_in_token(t_token *token, t_list *env_list, char *dollar_pos)
{
	char	*remaining;
	char	tmp_c;
	char	*new_arg;

	remaining = token->arg;
	new_arg = ft_strdup("");
	while (remaining)
	{
		dollar_pos = ft_strchr(remaining, '$');
		if (dollar_pos)
		{
			prepare_concat(&dollar_pos, &new_arg, &remaining, &tmp_c);
			new_arg = concat_expansion(new_arg, dollar_pos, env_list);
			*remaining = tmp_c;
		}
		else
		{
			if (not_empty(remaining))
				new_arg = concat_remaining(new_arg, remaining);
			remaining = NULL;
		}
	}
	token->arg = new_arg;
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
			expand_in_token(token, env_list, dollar_exists);
		cursor = cursor->next;
	}
	reformat(*redirs);
	return (*redirs);
}

void	split_token(t_list *cursor)
{
	char	**arg_split;
	t_token	*token;
	t_list	*new_node;
	int		i;

	arg_split = NULL;
	token = cursor->content;
	arg_split = ft_split(token->arg, ' ');
	display_token_to_be_splitted(token, arg_split);
	i = 0;
	token->arg = arg_split[i++];
	while (arg_split[i])
	{
		new_node = ft_alloc(sizeof(t_list));	
		token = ft_alloc(sizeof(t_token));
		token->arg = arg_split[i];
		token->type = ARG;
		new_node->content = token;
		new_node->previous = cursor;
		new_node->next = cursor->next;
		cursor->next = new_node;
		cursor = cursor->next;
		i++;
	}
	ft_free_ptr((void**)&arg_split);
}

void	esc_space_to_neg(char *str)
{
	enum e_state	state;
	int				i;

	state = NORMAL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && state == NORMAL)
			state = D_QUOTE;
		else if (str[i] == '\\' && state == NORMAL)
			state = B_SLASH;
		else if (str[i] == '\'' && state == NORMAL)
			state = S_QUOTE;
		else if (str[i] == ' ' &&
				(state == D_QUOTE
					|| state == S_QUOTE 
					|| state == B_SLASH))
			str[i] = -str[i];
		else if ((str[i] == '\'' && state == S_QUOTE)
				|| (str[i] == '\"' && state == D_QUOTE)
				|| state == B_SLASH)
			state = NORMAL;
		i++;
	}
}



void	remove_empty_tokens(t_list **args)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*lst;

	while (*args && token_has_empty_arg((*args)->content))
	{
		tmp = *args;
		*args = (*args)->next;
		free_token(tmp->content);
		ft_free_ptr((void**)&tmp);
	}
	prev = NULL;
	lst = *args;
	while (lst)
	{
		tmp = lst;
		if (token_has_empty_arg(lst->content))
		{
			tmp = lst;
			prev->next = tmp->next;
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

t_list	*expand_args(t_list **args, t_list *env_list)
{
	t_list	*cursor;
	t_token	*token;
	char	*dollar_exists;
	char	*space_exists;

	cursor = *args;
	dollar_exists = NULL;
	while (cursor)
	{
		space_exists = NULL;
		token = cursor->content;
		dollar_exists = ft_strchr(token->arg, '$');
		if (dollar_exists)
		{
			expand_in_token(token, env_list, dollar_exists);
			esc_space_to_neg(token->arg);
			space_exists = ft_strchr(token->arg, ' ');
			if (space_exists)
				split_token(cursor);
		}
		cursor = cursor->next;
	}
	remove_empty_tokens(args);
	reformat(*args);
	return (*args);
}
