#include "minishell.h"

static int	get_x(char *buf, int *pos)
{
	int	i;
	int	x;
	int	pow;

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
	int	y;
	int	pow;
	int	i;

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
			ft_putstr_fd("get_cursor_pos: error reading response!\n", 2);
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

void	erase_input(t_input *buff, struct winsize w
		/*char *pwd_val*/)
{
//	size_t	pwd_len;

//	pwd_len = 0;
//	if (pwd_val != NULL)
//		pwd_len = ft_strlen(pwd_val);
//	while (pwd_len + buff->i > w.ws_col)
	while (PROMPT_LEN + buff->i > w.ws_col)
	{
		exec_termcap("dl");
		exec_termcap("up");
		buff->i -= w.ws_col;
	}
	exec_termcap("dl");
}
