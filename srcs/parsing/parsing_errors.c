#include "minishell.h"

/*
** SYNTAX ERRORS SETS LAST RETURN TO 2
*/

static void	escaping_err_msg(t_parse *p)
{
	ft_putstr_fd("minishell - ESCAPING syntax error because of unterminated "
			, STDERR_FILENO);
	if (p->state == D_QUOTE)
		ft_putendl_fd("' \" '", STDERR_FILENO);
	else if (p->state == B_SLASH)
		ft_putendl_fd("' \\ '", STDERR_FILENO);
	else if (p->state == S_QUOTE)
		ft_putendl_fd("\" ' \"", STDERR_FILENO);
	ft_lstclear(&p->tokens, free_token);
}

static void	typing_err_msg(t_parse *p, int ret_tokenizing)
{
	ft_putstr_fd("minishell - TYPE syntax error near unexpected symbol ",
			STDERR_FILENO);
	if (ret_tokenizing == -NEWLINE)
		ft_putendl_fd("\" newline \"", STDERR_FILENO);
	else if (ret_tokenizing == -'>' && p->buffer_start[1] == '>')
		ft_putendl_fd("\'>>\'", STDERR_FILENO);
	else
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putchar_fd(-ret_tokenizing, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	ft_lstclear(&p->tokens, free_token);
}

t_list		*check_parsing_errors(t_parse *p, int ret_tokenizing)
{
	if (p->line_len == 0)
	{
		ft_putstr_fd("minishell - ALLOC error\n", STDERR_FILENO);
		return (NULL);
	}
	else if (p->state != NORMAL)
		escaping_err_msg(p);
	else if (ret_tokenizing < 0)
		typing_err_msg(p, ret_tokenizing);
	free(p->buffer_start);
	return (p->tokens);
}
