#include "minishell.h"

static int	get_x(char *buf, int *pos)
{
	int		i;
	int		x;
	int		pow;

	i = *pos;
	x = 0;
	pow = 1;
	while (buf[i] != ';')
	{
		x = x + (buf[i] - '0') * pow;
		i--;
		pow *= 10;
	}
	*pos = i;
	return (x);
}

static int	get_y(char *buf, int *pos)
{
	int		y;
	int		pow;
	int		i;

	i = *pos;
	y = 0;
	pow = 1;
	while (buf[i] != '[')
	{
		y = y + (buf[i] - '0') * pow;
		i--;
		pow *= 10;
	}
	return (y);
}

int	get_cursor_pos(int *y, int *x)
{
	char	buf[30];
	int		ret;
	int		i;
	char	ch;

	i = 0;
	ch = 0;
	write(1, "\033[6n", 4);
	while (ch != 'R')
	{
		ret = read(0, &ch, 1);
		if (!ret)
		{
			ft_putstr_fd("get_cursor_pos: error reading response!\n", STDERR_FILENO);
			return (1);
		}
		buf[i++] = ch;
	}
	if (i < 2)
		return (1);
	i -= 2;
	*x = get_x(buf, &i);
	i--;
	*y = get_y(buf, &i);
	return (0);
}

int	get_line_width(void)
{
	int				size;
	struct winsize	w;

	size = 0;
	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void	move_cursor(int side)
{
	int				x;
	int				y;
	struct winsize	w;

	get_cursor_pos(&y, &x);
	ioctl(0, TIOCGWINSZ, &w);
	if (side == RIGHT)
	{
		if (x == w.ws_col)
		{
			exec_termcap("sc");
			exec_termcap("do");
			exec_termcap("cr");
		}
	}
	else if (side == LEFT)
	{
		if (x == 1)
		{
			exec_termcap("rc");
			exec_termcap("ce");
			get_cursor_pos(&y, &x);
			if (w.ws_row == y)
				exec_termcap("up");
		}
	}
}
