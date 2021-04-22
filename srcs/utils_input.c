#include "minishell.h"

int		is_ctrl_keys(char c, int *stop, t_buff *buff, t_list *history)
{
	if (c == ctrl_value('d'))
		*stop = 1;
	else if (c == ctrl_value('u'))
		clear_line(buff);
	else if (c == ctrl_value('h'))
	{
		display_history(history);
		prompt(global.env_list, buff);
	}
	else if (c == ctrl_value('s'))
	{
		printf("history size = %d\r\n", ft_lstsize(history));
		prompt(global.env_list, buff);
	}
	else
		return (0);
	return (1);
}

int		arrow_value(void)
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