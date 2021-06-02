#include "minishell.h"

static void	perform_sup_redir(t_token *node)
{
	int		fd_redir;
	int		fd_file;

	fd_redir = -1;
	fd_file = -1;
	fd_redir = dup(1);
	fd_file = open(node->arg, O_CREAT);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
}

int			perform_redirections(t_list *redirs)
{
	t_token	*node;

	if (!redirs)
		return (0);
	display_tokens(redirs);
	while (redirs)
	{
		node = redirs->content;
		if (node->type == REDIR_SUP)
			perform_sup_redir((t_token*)redirs->content);
		redirs = redirs->next;
	}
	return (1);
}