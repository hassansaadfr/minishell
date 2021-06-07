#include "minishell.h"

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
