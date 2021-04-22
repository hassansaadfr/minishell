#include "minishell.h"

int		get_strarr_size(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int		handle_errno(int err, char *binary, char *arg)
{
	if (err != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(binary, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (err != E2BIG)
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\r\n", STDERR_FILENO);
	}
	return (errno);
}
