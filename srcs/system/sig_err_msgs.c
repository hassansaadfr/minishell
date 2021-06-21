#include "minishell.h"

void	print_sig_err(int pid, int sig, char *binary)
{
	if (sig == 0 || sig == 13)
		return ;
	ft_putstr_fd("[1]\t", STDERR_FILENO);
	ft_putnbr_fd(pid, STDERR_FILENO);
	if (sig == 1)
		ft_putstr_fd("\tHangup\t", STDERR_FILENO);
	else if (sig == 2)
		ft_putstr_fd("\tInterrupt\t", STDERR_FILENO);
	else if (sig == 3)
		ft_putstr_fd("\tQuit\t", STDERR_FILENO);
	else if (sig == 4)
		ft_putstr_fd("\tIllegal instruction\t", STDERR_FILENO);
	else if (sig == 5)
		ft_putstr_fd("\tTrace/breakpoint trap\t", STDERR_FILENO);
	else if (sig == 6)
		ft_putstr_fd("\tAborted\t", STDERR_FILENO);
	else if (sig == 7)
		ft_putstr_fd("\tBus error\t", STDERR_FILENO);
	else if (sig == 8)
		ft_putstr_fd("\tFloating point exception\t", STDERR_FILENO);
	else if (sig == 9)
		ft_putstr_fd("\tKilled\t", STDERR_FILENO);
	else if (sig == 10)
		ft_putstr_fd("\tUser defined signal 1\t", STDERR_FILENO);
	else if (sig == 11)
		ft_putstr_fd("\tSegmentation fault\t", STDERR_FILENO);
	else if (sig == 12)
		ft_putstr_fd("\tUser defined signal 2\t", STDERR_FILENO);
	else if (sig == 14)
		ft_putstr_fd("\tAlarm clock\t", STDERR_FILENO);
	else if (sig == 15)
		ft_putstr_fd("\tTerminated\t", STDERR_FILENO);
	else if (sig == 16)
		ft_putstr_fd("\tStack fault\t", STDERR_FILENO);
	ft_putendl_fd(binary, STDERR_FILENO);
}
