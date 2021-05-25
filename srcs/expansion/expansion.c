#include "minishell.h"

/*
   1 - trouver le '$'
//2 - incrementer le ptr sur la pos ==> on est sur la position de la premiere lettre de la key
3 - trouver le bout de str qui constitue la key
4 - calculer la longueur de la key 
5 - ft_substr la key
6 - expansion = get_env(key)
 */

void	display_expansion_parts(char *beginning, char *expansion, char *remaining, int key_len)
{
	printf("key_len\t\t=\t%d\n", key_len);
	printf("beginning\t=\t\"%s\"\n", beginning);
	if (expansion)
		printf("expansion\t=\t\"%s\"\n", expansion);
	printf("remaining\t=\t\"%s\"\n\n", remaining);
}

int		is_expansion_delimiter(char c, int key_len)
{	
	if (key_len == 0)
		return (c == '\0' || c == '\'' || c == '\"' || c == '\\'
				|| c == -'\0' || c == -'\'' || c == -'\"' || c == -'\\');
	else
		return (c == '\0' || c == '\'' || c == '\"' || c == '\\' || c == ' ' || c == '$'
				|| c == -'\0' || c == -'\'' || c == -'\"' || c == -'\\' || c == -' ');
}

int		dollar_must_be_printed(char c)
{
	return (c == '\0' || c == '\\' || c == ' ' || c == -' ' || c == '\"');
}

void	expand_fd(t_token *token, t_list *env_list, char *dollar_pos)
{
	t_list		*node;
	t_expand	exp;

	init_expand_struct(&exp, token);
	while (dollar_pos)
	{
		exp.key_len = 0;
		exp.expansion = NULL;
		if (dollar_must_be_printed(dollar_pos[1]))
			dollar_pos = ft_strchr(dollar_pos + 1, '$');
		else
		{
			exp.beginning = token->arg;
			while (is_expansion_delimiter(dollar_pos[exp.key_len], exp.key_len) == 0)
				exp.key_len++;
			exp.tmp_remaining = exp.remaining;
			exp.remaining = dollar_pos + exp.key_len;
			exp.tmp_c = *exp.remaining;
			*dollar_pos = '\0';
			if (exp.tmp_remaining != NULL)
			{
				exp.tmp_new_arg = exp.new_arg;
				exp.new_arg = ft_strjoin(exp.new_arg, exp.tmp_remaining);
				exp.tmp_remaining = NULL;
				ft_free_ptr((void**)&exp.tmp_new_arg);
				exp.tmp_new_arg = NULL;
			}
			*exp.remaining = '\0';
			node = get_env(env_list, dollar_pos + 1);
			if (node)
				exp.expansion = ((t_env*)node->content)->value;
			*exp.remaining = exp.tmp_c;
			if (exp.expansion)
			{
				if (exp.new_arg == NULL)
					exp.new_arg = ft_strjoin(exp.beginning, exp.expansion);
				else
				{
					exp.tmp_new_arg = exp.new_arg;
					exp.new_arg = ft_strjoin(exp.new_arg, exp.expansion);
					exp.expansion = NULL;
					ft_free_ptr((void**)&exp.tmp_new_arg);
					exp.tmp_new_arg = NULL;
				}
			}
			dollar_pos = ft_strchr(exp.remaining, '$');
		}
	}
	if (exp.remaining != NULL && not_empty(exp.remaining))
	{
		if (exp.new_arg == NULL)
			exp.tmp_new_arg = token->arg;
		else
			exp.tmp_new_arg = exp.new_arg;
		exp.new_arg = ft_strjoin(exp.tmp_new_arg, exp.remaining);
		if (exp.tmp_new_arg == token->arg)
			ft_free_ptr((void**)&token->arg);
		else
		{
			ft_free_ptr((void**)&exp.tmp_new_arg);
			ft_free_ptr((void**)&token->arg);
		}
	}
	if (exp.new_arg)
		token->arg = exp.new_arg;
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
