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

void	expand_fd(t_token *token, t_list *env_list, char *dollar_pos)
{
	t_list	*node;
	int		key_len;
	char	*beginning;
	char	*remaining;
	char	*expansion;
	char	*new_arg;
	char	tmp_c;
	char	*tmp_new_arg;
	char	*tmp_remaining;

	new_arg = NULL;
	remaining = NULL;
	while (dollar_pos)
	{
		key_len = 0;
		expansion = NULL;
		// IF '$' MUST BE LEFT AS IS
		if (dollar_pos[1] == '\0' || dollar_pos[1] == '\\' || dollar_pos[1] == ' '
				|| dollar_pos[1] == -' ' || dollar_pos[1] == '\"')
			dollar_pos = ft_strchr(dollar_pos + 1, '$');
		// IF EXPANSION NEEDED
		else
		{
			beginning = token->arg;
			while (is_expansion_delimiter(dollar_pos[key_len], key_len) == 0)
				key_len++;
			tmp_remaining = remaining;
			remaining = dollar_pos + key_len;
			tmp_c = *remaining;
			*dollar_pos = '\0';
			if (tmp_remaining != NULL)
			{
				tmp_new_arg = new_arg;
				new_arg = ft_strjoin(new_arg, tmp_remaining);
				tmp_remaining = NULL;
				ft_free_ptr((void**)&tmp_new_arg);
				tmp_new_arg = NULL;
			}
			*remaining = '\0';
			node = get_env(env_list, dollar_pos + 1);
			if (node)
				expansion = ((t_env*)node->content)->value;
			*remaining = tmp_c;
			if (expansion)
			{
				// PASS ESC CHARS AND SPACES IN expansion TO NEGATIVE HERE
				if (new_arg == NULL)
				{
					display_expansion_parts(beginning, expansion, remaining, key_len);
					new_arg = ft_strjoin(beginning, expansion);
				}
				else
				{
					display_expansion_parts(new_arg, expansion, remaining, key_len);
					tmp_new_arg = new_arg;
					new_arg = ft_strjoin(new_arg, expansion);
					ft_free_ptr((void**)&tmp_new_arg);
					tmp_new_arg = NULL;
				}
			}
			dollar_pos = ft_strchr(remaining, '$');
		}
	}
	/*
	if (new_arg != NULL)
	{
		if (not_empty(remaining))
			new_arg = ft_strjoin(new_arg, remaining);
		ft_free_ptr((void**)&token->arg);
		token->arg = new_arg;
	}
	*/
	if (not_empty(remaining))
	{
		if (new_arg == NULL)
		{
			tmp_new_arg = token->arg;
			new_arg = ft_strjoin(tmp_new_arg, remaining);
			ft_free_ptr((void**)&tmp_new_arg);
		}
		else
		{
			tmp_new_arg = new_arg;
			new_arg = ft_strjoin(tmp_new_arg, remaining);
			ft_free_ptr((void**)&tmp_new_arg);
			ft_free_ptr((void**)&token->arg);
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
			expand_fd(token, env_list, dollar_exists);
		cursor = cursor->next;
	}
	return (*redirs);
}
