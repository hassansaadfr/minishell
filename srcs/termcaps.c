#include "minishell.h"

/*
// ALREADY COPIED
int		init_termcaps(void)
{
	int		ret_tgetent;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_putstr_fd("ERROR - \"TERM\" not set in env\r\n", STDERR_FILENO);
		return (0);
	}
	ret_tgetent = tgetent(NULL, term_type);
	if (ret_tgetent == -1)
	{
		ft_putstr_fd("ERROR - Could not access Termcaps DB\r\n", STDERR_FILENO);
		return (0);
	}
	if (ret_tgetent == 0)
	{
		ft_putstr_fd("ERROR - Termcap type \"", STDERR_FILENO);
		ft_putstr_fd(term_type, STDERR_FILENO);
		ft_putstr_fd("\" is not in Termcap DB\r\n", STDERR_FILENO);
		return (0);
	}
	return (1);
// ALREADY COPIED
}
*/

int		put_termcap(int c)
{
	char	ch_c;

	ch_c = (char)c;
	write(STDIN_FILENO, &c, 1);
	return (1);
}

void	exec_termcap(char *termcap_name)
{
	char	*termcap_value;

	termcap_value = tgetstr(termcap_name, NULL);
	tputs(termcap_value, 1, put_termcap);
}

void	delete_char(t_buff *buff)
{
	if (buff->i >= 1)
	{
		exec_termcap("le");
		exec_termcap("dc");
		buff->buffer[--buff->i] = '\0';
	}
}

void	clear_line(t_buff *buff)
{
	exec_termcap("dl");
	buff->i = 0;
	prompt(global.env_list, buff);
}
