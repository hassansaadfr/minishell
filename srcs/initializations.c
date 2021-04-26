#include "minishell.h"

int		init_buff_and_history(t_buff *buff, t_list **history)
{
	buff->buffer = malloc(INPUT_MAX);
	if (buff->buffer == NULL)
		return (1);
	ft_bzero(buff->buffer, INPUT_MAX);
	buff->backup = malloc(INPUT_MAX);
	if (buff->backup == NULL)
	{
		free(buff->buffer);
		return (1);
	}
	ft_bzero(buff->backup, INPUT_MAX);
	buff->pos = NULL;
	buff->i = 0;
	buff->factor = 1;
	*history = NULL;
	g_global.buff = buff;
	return (0);
}

int		init_termcaps(void)
{
	int		ret_tgetent;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_putstr_fd("ERROR - \"TERM\" not set in env\n", STDERR_FILENO);
		return (0);
	}
	ret_tgetent = tgetent(NULL, term_type);
	if (ret_tgetent == -1)
	{
		ft_putstr_fd("ERROR - Could not access Termcaps DB\n", STDERR_FILENO);
		return (0);
	}
	if (ret_tgetent == 0)
	{
		ft_putstr_fd("ERROR - Termcap type \"", STDERR_FILENO);
		ft_putstr_fd(term_type, STDERR_FILENO);
		ft_putstr_fd("\" is not in Termcap DB\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}
