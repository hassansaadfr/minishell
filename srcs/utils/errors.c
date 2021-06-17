#include "minishell.h"

void	print_err_with_quote(char *binary, char *arg, char *err)
{
	char	*with_quote;
	char	*tmp;

	with_quote = NULL;
	tmp = NULL;
	tmp = ft_strjoin("« ", arg);
	with_quote = ft_strjoin(tmp, " » ");
	print_err(binary, with_quote, err);
	ft_free_ptr((void **)&tmp);
	ft_free_ptr((void **)&with_quote);
}

/* 	TENTATIVE FIX 'line 1:' if (!isatty(STDIN_FILENO) && g_global.pid != 0) */
void	print_err(char *binary, char *arg, char *err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!isatty(STDIN_FILENO))
		ft_putstr_fd("line 1: ", STDERR_FILENO);
	if (binary)
	{
		ft_putstr_fd(binary, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err, STDERR_FILENO);
}

int	return_err_msg(char *problem_pos, char *err_msg, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (problem_pos && not_empty(problem_pos) == TRUE)
	{
		ft_putstr_fd(problem_pos, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (err);
}
