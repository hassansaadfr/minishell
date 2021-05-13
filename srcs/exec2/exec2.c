#include "minishell.h"

void	display_splitted_cmd(t_list *cmd, int debug_i)
{
	printf("========================== CMD %2i ==========================\n", debug_i++);
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

int		executing(t_list *tokens, t_list *env_list, t_list *history)
{
	(void)env_list;
	(void)history;
	int		debug_i = 0;
	t_list	*cmd;

	cmd = NULL;
	while (tokens)
	{
		cmd = split_smc(&tokens);
		display_splitted_cmd(cmd, debug_i++);
		ft_lstclear(&cmd, free_token);
	}
	return (0);
}
