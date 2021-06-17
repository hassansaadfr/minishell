#include "minishell.h"

static void	move_cursor_up_right(void)
{
	int		i;

	i = 0;
	exec_termcap("up");
	while (i < PROMPT_LEN + g_global.buff->i)
	{
		exec_termcap("nd");
		i++;
	}
}

void	move_cursor_back(void)
{
	int				x;
	int				y;
	struct winsize	w;

	get_cursor_pos(&y, &x);
	ioctl(0, TIOCGWINSZ, &w);
	get_cursor_pos(&y, &x);
	if (x == 1)
		move_cursor_up_right();
	else
		exec_termcap("le");
}
