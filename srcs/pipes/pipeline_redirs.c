#include "minishell.h"

static int	perform_sup_redir(t_token *node, int out)
{
	int		fd_file;

	errno = 0;
	fd_file = -1;
	fd_file = open(node->arg, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_file == -1)
		return (errno);
	if (dup2(fd_file, out) == -1)
	{
		close(fd_file);
		return (errno);
	}
	close(fd_file);
	return (0);
}

static int	perform_dsup_redir(t_token *node, int out)
{
	int		fd_file;

	errno = 0;
	fd_file = -1;
	fd_file = open(node->arg, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (fd_file == -1)
		return (errno);
	if (dup2(fd_file, out) == -1)
	{
		close(fd_file);
		return (errno);
	}
	close(fd_file);
	return (0);
}

static int	perform_inf_redir(t_token *node, int in)
{
	int		fd_file;

	errno = 0;
	fd_file = -1;
	fd_file = open(node->arg, O_RDONLY);
	if (fd_file == -1)
		return (errno);
	if (dup2(fd_file, in) == -1)
	{
		close(fd_file);
		return (errno);
	}
	close(fd_file);
	return (0);
}

int	perform_pipeline_redirections(t_list *r, int *in_out_tbc)
{
	t_token	*node;
	int		ret_redir;

	ret_redir = 0;
	while (r)
	{
		node = r->content;
		if (node->type == REDIR_SUP)
			ret_redir = perform_sup_redir(r->next->content, in_out_tbc[OUT]);
		else if (node->type == REDIR_DSUP)
			ret_redir = perform_dsup_redir(r->next->content, in_out_tbc[OUT]);
		else if (node->type == REDIR_INF)
			ret_redir = perform_inf_redir(r->next->content, in_out_tbc[IN]);
		if (ret_redir != 0)
			return (return_err_msg("redirection", strerror(ret_redir), errno));
		r = r->next;
	}
	return (0);
}
