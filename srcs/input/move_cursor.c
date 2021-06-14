#include "minishell.h"

static void	move_cursor_up_right(void)
{
	int		pwd_len;
	int		i;
	char	*pwd_var;

	i = 0;
	pwd_len = 3;
	pwd_var = NULL;
	pwd_var = get_env_value(g_global.env_list, "PWD");
	if (pwd_var != NULL)
		pwd_len = ft_strlen(pwd_var);
	pwd_len += 3;
	pwd_len += g_global.buff->i;
	exec_termcap("up");
	while (i < pwd_len)
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
