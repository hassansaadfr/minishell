#include "minishell.h"

void	display_splitted_cmd(t_list *cmd, int debug_i, char *type)
{
	printf("========================== %3s %2i ==========================\n",
			type, debug_i++);
	display_tokens(cmd);
}

void	del_smc_node(t_list *tmp)
{
	tmp->previous = NULL;
	tmp->next = NULL;
	ft_lstdelone(&tmp, free_token);
}

t_list	*split_smc(t_list **tokens)
{
	t_list	*cmd;
	t_list	*tmp;

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

t_list	*find_first_arg_node(t_list *tokens)
{
	while (tokens)
	{
		if (((t_token*)tokens->content)->type == ARG)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_list	*isolate_redirs(t_list **redirs_and_args)
{
	t_list	*redirs;
	t_token	*token;
	t_list	*tmp;
	t_list	*to_remove;

	redirs = NULL;
	// DEBUT DE LISTE
	while (*redirs_and_args && 
			(is_redir(((t_token*)(*redirs_and_args)->content)->type)
			 || ((t_token*)(*redirs_and_args)->content)->type == FD))
	{
		tmp = *redirs_and_args;
		*redirs_and_args = (*redirs_and_args)->next;
		tmp->next = NULL;
		tmp->previous = NULL;
		ft_lstadd_back(&redirs, tmp);
	}
	// EN MILIEU DE LISTE
	token = NULL;
	tmp = *redirs_and_args;
	while (tmp)
	{
		token = NULL;
		tmp = *redirs_and_args;
		while (tmp)
		{
			to_remove = tmp;
			token = to_remove->content;
			tmp = tmp->next;
			if (is_redir(token->type) || token->type == FD)
			{
				ft_lstdelone(&to_remove, NULL);
				to_remove->previous = NULL;
				to_remove->next = NULL;
				ft_lstadd_back(&redirs, to_remove);
			}
		}
	}
	return (redirs);
}

int		execute_simple_cmd(t_list *tokens, t_list *env_list, int debug_i)
{
	(void)env_list;
	int		ret_exec;
	//	char	**argv;
	t_list	*redirs;

	redirs = isolate_redirs(&tokens);
	if (tokens)
		display_splitted_cmd(tokens, debug_i, "CMD");
	if (redirs)
		display_splitted_cmd(redirs, debug_i, "RDR");
	//	argv = make_argv_arr(tokens); 

	ret_exec = 0;
	return (0);
}

int		executing(t_list *tokens, t_list *env_list, t_list *history)
{
	(void)env_list;
	(void)history;
	int		debug_i = 0;
	t_list	*indpdt_cmd;
	int		ret_exec;

	indpdt_cmd = NULL;
	ret_exec = 0;
	while (tokens)
	{
		indpdt_cmd = split_smc(&tokens);
		//	display_splitted_cmd(indpdt_cmd, debug_i++, "CMD");
		// 1 - EXPANSION
		// 2 - EXECUTION
		ret_exec = execute_simple_cmd(indpdt_cmd, env_list, debug_i++);
		ft_lstclear(&indpdt_cmd, free_token);
	}
	return (ret_exec);
}
