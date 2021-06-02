#include "minishell.h"

static void	perform_sup_redir(t_token *node)
{
	int		fd_backup;
	int		fd_file;

	fd_backup = -1;
	fd_file = -1;
	fd_backup = dup(STDOUT_FILENO);
	fd_file = open(node->arg, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
}

int			perform_redirections(t_list *redirs)
{
	t_token	*node;
	int		backup;

	backup = -1;
	if (!redirs)
		return (0);
	display_tokens(redirs);
	while (redirs)
	{
		node = redirs->content;
		if (node->type == REDIR_SUP)
			perform_sup_redir((t_token*)redirs->next->content);
		redirs = redirs->next;
	}
	return (1);
}
