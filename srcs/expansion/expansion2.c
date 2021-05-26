#include "minishell.h"

char	*get_expansion_value(char *key_pos, t_list *env_list)
{
	t_list	*node;
	char	*env_value;

	env_value = NULL;
	node = get_env(env_list, key_pos);
	if (node)
		env_value = ((t_env*)node->content)->value;
	return (env_value);
}

char	*concat_expansion(char *new_arg, char *key_pos, t_list *env_list)
{
	char	*tmp;
	char	*expansion;

	if (*key_pos == '\0' || *key_pos == ' ' || *key_pos == -' '
			|| *key_pos == '\\' || *key_pos == -'\\')
		expansion = ft_strdup("$");
	else
		expansion = get_expansion_value(key_pos, env_list);
	if (expansion != NULL)
	{
	// PASS ESC CHARS AND SPACES IN expansion TO NEGATIVE HERE
		tmp = new_arg;
		new_arg = ft_strjoin(new_arg, expansion);
		ft_free_ptr((void**)&tmp);
//		ft_free_ptr((void**)&expansion);
	}
	return (new_arg);
}

char	*concat_remaining(char *new_arg, char *remaining)
{
	char	*tmp;

	tmp = new_arg;
	new_arg = ft_strjoin(new_arg, remaining);
	ft_free_ptr((void**)&tmp);
	return (new_arg);
}

void	prepare_concat(char **dollar_pos, char **new_arg, char **remaining,
		char *tmp_c)
{
	char	*tmp;

	**dollar_pos = '\0';
	if (*remaining != *dollar_pos)
	{
		tmp = *new_arg;
		*new_arg = ft_strjoin(*new_arg, *remaining);
		ft_free_ptr((void**)&tmp);
	}
	(*dollar_pos)++;
	*remaining = *dollar_pos;
	while (**remaining && (ft_isalnum(**remaining) || **remaining == '_'))
		(*remaining)++;
	*tmp_c = **remaining;
	**remaining = '\0';
}

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
	return (*redirs);
}
