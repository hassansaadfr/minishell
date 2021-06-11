#include "minishell.h"

static int	perform_sup_redir(t_token *node)
{
	int		fd_file;

	if (ft_strlen(node->arg) == 0)
	{
		print_err(NULL, NULL, AMBIGUOUS_REDIRECT);
		return (1);
	}
	errno = 0;
	fd_file = -1;
	fd_file = open(node->arg, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (errno != 0)
	{
		print_err(node->arg, NULL, strerror(errno));
		return (1);
	}
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	return (0);
}

static int	perform_dsup_redir(t_token *node)
{
	int		fd_file;

	if (ft_strlen(node->arg) == 0)
	{
		print_err(NULL, NULL, AMBIGUOUS_REDIRECT);
		return (1);
	}
	errno = 0;
	fd_file = -1;
	fd_file = open(node->arg, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (errno != 0)
	{
		print_err(node->arg, NULL, strerror(errno));
		return (1);
	}
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	return (0);
}

static int	perform_inf_redir(t_token *node)
{
	int		fd_file;

	if (ft_strlen(node->arg) == 0)
	{
		print_err(NULL, NULL, AMBIGUOUS_REDIRECT);
		return (1);
	}
	errno = 0;
	fd_file = -1;
	fd_file = open(node->arg, O_RDONLY);
	if (errno != 0)
	{
		print_err(node->arg, NULL, strerror(errno));
		return (1);
	}
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	return (0);
}

int	perform_redirections(t_list *redirs)
{
	t_token	*node;
	int		ret_redir;

	ret_redir = 0;
	while (redirs)
	{
		node = redirs->content;
		if (node->type == REDIR_SUP)
			ret_redir = perform_sup_redir((t_token *)redirs->next->content);
		else if (node->type == REDIR_DSUP)
			ret_redir = perform_dsup_redir((t_token *)redirs->next->content);
		else if (node->type == REDIR_INF)
			ret_redir = perform_inf_redir((t_token *)redirs->next->content);
		if (ret_redir != 0)
			return (ret_redir);
		redirs = redirs->next;
	}
	return (0);
}
