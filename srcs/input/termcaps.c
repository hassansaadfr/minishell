#include "minishell.h"

int	put_termcap(int c)
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

void	delete_char(t_input *buff)
{
	if (buff->i >= 1)
	{
		move_cursor_back();
		exec_termcap("dc");
		buff->buffer[--buff->i] = '\0';
	}
}

void	clear_line(t_input *buff)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	erase_input(buff, w);
	print_prompt();
	buff->i = 0;
}
