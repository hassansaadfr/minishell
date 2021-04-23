#include "minishell.h"

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
	prompt();
}
