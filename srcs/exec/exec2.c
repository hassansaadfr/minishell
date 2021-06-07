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

void	sanitize(char *str)
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
			sanitize(token->arg);
		list = list->next;
	}
}

void	display_token(t_list *tokens)
{
	t_list *tmp;
	t_token *tok;

	tmp = tokens;
	while (tmp)
	{
		tok = tmp->content;
		printf("token : %s\n", tok->arg);
		tmp = tmp->next;
	}
}

int		execute_simple_cmd(t_list *tokens, t_list *env_list, int debug_i)
{
	(void)env_list;
	t_list	*redirs;
	char	**cmds;

	(void)debug_i;
	cmds = NULL;
	redirs = isolate_redirs(&tokens);
	if (tokens)
		reformat(tokens);
	if (redirs)
		reformat(redirs);
	return (perform_execution(redirs, tokens, env_list));
}

int		executing(t_list *tokens, t_list *env_list, t_list *history)
{
	(void)history;
	int		debug_i = 0;
	t_list	*indpdt_cmd;
	int		ret_exec;

	indpdt_cmd = NULL;
	ret_exec = 0;
	while (tokens)
	{
		indpdt_cmd = isolate_indpdt_cmd(&tokens);
		// display_splitted_cmd(indpdt_cmd, debug_i, "CMD");
		ret_exec = execute_simple_cmd(indpdt_cmd, env_list, debug_i++);
	}
	return (ret_exec);
}
