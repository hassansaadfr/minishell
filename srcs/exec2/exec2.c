#include "minishell.h"

int		contains_esc_or_neg_chars(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '\"' || str[i] == '\'' || str[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

void	remove_quoting_chars(char *str)
{
	int		reader;
	int		writer;

	reader = 0;
	writer = 0;
	while (str[reader])
	{
		if (ft_strchr("\"\'\\", str[reader]) == NULL)
		{
			if (str[reader] < 0)
				str[reader] = -str[reader];
			str[writer++] = str[reader];
		}
		reader++;
	}
	str[writer] = '\0';
}

void	reformat(t_list *list)
{
	t_token		*token;

	while (list)
	{
		token = list->content;
		if (contains_esc_or_neg_chars(token->arg))	
			remove_quoting_chars(token->arg);
		list = list->next;
	}
}

int		execute_simple_cmd(t_list *tokens, t_list *env_list)
{
	(void)env_list;
	int		ret_exec;
	t_list	*redirs;

	redirs = isolate_redirs(&tokens);
	if (tokens)
		tokens = expand_args(&tokens, env_list);
	if (redirs)
		redirs = expand_redirs(&redirs, env_list);
	ft_lstclear(&redirs, free_token);
	ft_lstclear(&tokens, free_token);
	ret_exec = 0;
	return (0);
}

int		executing(t_list *tokens, t_list *env_list, t_list *history)
{
	(void)history;
	t_list	*indpdt_cmd;
	int		ret_exec;

	indpdt_cmd = NULL;
	ret_exec = 0;
	while (tokens)
	{
		indpdt_cmd = isolate_indpdt_cmd(&tokens);
		ret_exec = execute_simple_cmd(indpdt_cmd, env_list);
	}
	return (ret_exec);
}
