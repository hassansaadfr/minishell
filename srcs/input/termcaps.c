#include "minishell.h"

int	put_termcap(int c)
{
	char	ch_c;

	ch_c = (char)c;
	write(STDIN_FILENO, &c, 1);
	return (1);
}

int	exec_termcap(char *termcap_name)
{
	char	*termcap_value;
	int		ret;

	ret = 0;
	termcap_value = tgetstr(termcap_name, NULL);
	ret = tputs(termcap_value, 1, put_termcap);
	return (ret);
}

void	delete_char(t_input *buff)
{
	if (buff->i >= 1)
	{
		exec_termcap("le");
		exec_termcap("dc");
		buff->buffer[--buff->i] = '\0';
	}
}

void	clear_line(t_input *buff)
{
	exec_termcap("dl");
	buff->i = 0;
	prompt();
}
