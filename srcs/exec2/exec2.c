#include "minishell.h"

int		execute_simple_cmd(t_list *tokens, t_list *env_list, int debug_i)
{
	(void)env_list;
	int		ret_exec;
	t_list	*redirs;

	// EXPANSION
	redirs = isolate_redirs(&tokens);
	if (tokens)
		display_splitted_cmd(tokens, debug_i, "ARG");
	if (redirs)
		display_splitted_cmd(redirs, debug_i, "RDR");
	ft_lstclear(&redirs, free_token);
	ft_lstclear(&tokens, free_token);
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
		display_splitted_cmd(indpdt_cmd, debug_i, "CMD");
		ret_exec = execute_simple_cmd(indpdt_cmd, env_list, debug_i++);
	}
	return (ret_exec);
}
