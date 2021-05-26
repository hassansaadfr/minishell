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

char	**token_list_to_array(t_list *token_list)
{
	int		size;
	char	**array;
	int		i;
	t_list	*tmp_lst;

	size = ft_lstsize(token_list);
	i = 0;
	array = ft_alloc(sizeof(char*) * (size + 1));
	array[size] = NULL;
	tmp_lst = token_list;
	while (tmp_lst)
	{
		t_token *tmp = tmp_lst->content;
		array[i] = ft_strdup(tmp->arg);
		i++;
		tmp_lst = tmp_lst->next;
	}
	return (array);
}

int		execute_simple_cmd(t_list *tokens, t_list *env_list, int debug_i)
{
	(void)env_list;
	int		ret_exec;
	t_list	*redirs;
	char	**cmds;

	(void)debug_i;
	cmds = NULL;
	redirs = isolate_redirs(&tokens);
	if (tokens)
	{
		//expand_args();
		reformat(tokens);
	}
	if (redirs)
	{
		//redirs = expand_redirs(&redirs, env_list);
		reformat(redirs);
	}
	// HASSAN - PERFORM REDIRS
	// HASSAN - EXEC(tokens)
	if  (tokens)
	{
		cmds = token_list_to_array(tokens);
		if (cmds)
		{
			execution(cmds, env_list, NULL);
			free_split(cmds);
		}
		ft_lstclear(&tokens, free_token);
	}
	ft_lstclear(&redirs, free_token);
	ret_exec = 0;
	return (0);
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
