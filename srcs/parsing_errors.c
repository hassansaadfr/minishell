#include "minishell.h"

t_list	*check_parsing_errors(t_parse p, int ret_tokenizing)
{
	if (p.state != NORMAL)
	{
		ft_putstr_fd("minishell - QUOTING syntax error\n", STDERR_FILENO);
		ft_lstclear(&p.tokens, free_token);
		return (NULL);
	}
	else if (ret_tokenizing < 0)
	{
		ft_putstr_fd("minishell - TYPE syntax error near unexpected symbol ",
				STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putchar_fd(-ret_tokenizing, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		ft_lstclear(&p.tokens, free_token);
		return (NULL);
	}
	else if (ret_tokenizing == 0)
	{
		ft_putstr_fd("minishell - alloc error\n", STDERR_FILENO);
		return (NULL);
	}
	return (p.tokens);
}
