#include "minishell.h"

void			disable_raw_mode(t_termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

t_termios		enable_raw_mode(void)
{
	t_termios	new_termios;
	t_termios	orig_termios;

	tcgetattr(STDIN_FILENO, &orig_termios);
	new_termios = orig_termios;
	new_termios.c_lflag &= ~(ICANON | ECHO);
	new_termios.c_iflag &= ~(IXON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
	return (orig_termios);
}
