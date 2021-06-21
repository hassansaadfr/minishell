#include "minishell.h"

static void	exit_ctrld(struct termios orig_termios)
{
	write(STDOUT_FILENO, "exit\n", 5);
	disable_raw_mode(orig_termios);
	ft_exit_free(g_global.last_return);
}

int	is_ctrl_keys(char c, t_input *buff, t_list *history,
struct termios orig_termios)
{
	if (c == ctrl_value('d') && buff->i == 0)
		exit_ctrld(orig_termios);
	if (c == ctrl_value('d') && buff->i > 0)
		write(1, "\a", STDOUT_FILENO);
	else if (c == ctrl_value('u'))
		clear_line(buff);
	else if (c == ctrl_value('h'))
		display_history(history);
	else if (c == ctrl_value('s') && DEBUG == 1)
	{
		printf("history size = %d\n", ft_lstsize(history));
		prompt();
	}
	else if (c == ctrl_value('c'))
	{
		ft_putstr_fd("^C\n", STDERR_FILENO);
		g_global.last_return = 130;
		prompt();
	}
	else
		return (0);
	return (1);
}

int	arrow_value(void)
{
	char	seq[3];

	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return (ESCAPE);
	if (read(STDIN_FILENO, &seq[1], 1) != 1)
		return (ESCAPE);
	if (seq[0] == '[' && seq[1] == 'A')
		return (UP_ARROW);
	else if (seq[0] == '[' && seq[1] == 'B')
		return (DN_ARROW);
	return (ESCAPE);
}

char	ctrl_value(char c)
{
	return ((c) & 0x1f);
}

int	not_empty(char *buffer)
{
	return (buffer[0] != '\0');
}
