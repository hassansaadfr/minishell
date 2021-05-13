#include "minishell.h"

void	display_splitted_cmd(t_list *cmd, int debug_i)
{
	printf("========================== CMD %2i ==========================\n",
			debug_i++);
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

int		execute_cmd(t_list *tokens, t_list *env_list)
{
	int		ret_exec;
	char	*path;
	char	**argv;
	t_list	*first_arg_node;

	first_arg_node = find_first_arg_node(tokens);

	ret_exec = 0;
}

int		executing(t_list *tokens, t_list *env_list, t_list *history)
{
	(void)env_list;
	(void)history;
	int		debug_i = 0;
	t_list	*cmd;
	int		ret_exec;

	cmd = NULL;
	ret_exec = 0;
	while (tokens)
	{
		cmd = split_smc(&tokens);
		display_splitted_cmd(cmd, debug_i++);
//		ret_exec = execute(cmd, env_list);
		ft_lstclear(&cmd, free_token);
		if (ret_exec != 0)
			ft_lstclear(&tokens, free_token);
	}
	return (ret_exec);
}
