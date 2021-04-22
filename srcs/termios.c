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
//	new_termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	new_termios.c_lflag &= ~(ICANON | ECHO);
//	new_termios.c_iflag &= ~(ICRNL | IXON);
	new_termios.c_iflag &= ~(IXON);
//	new_termios.c_oflag &= ~(OPOST);
	new_termios.c_cc[VMIN] = 0;
	new_termios.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
	return (orig_termios);
}
