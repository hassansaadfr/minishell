#include "minishell.h"

void	display_history(t_list *hist)
{
	int		i;

	if (DEBUG == 1)
	{
		printf("\n");
		i = 0;
		while (hist)
		{
			printf("%d\tcur: %p\t\"%10.10s\"\tprv: %p\tnxt: %p\n", i++, hist,
				hist->content, hist->previous, hist->next);
			hist = hist->next;
		}
		prompt();
	}
}

void	add_to_history(t_input *buff, t_list **history)
{
	char	*line;
	t_list	*new_node;

	if (not_empty(buff->buffer))
	{
		line = ft_strdup(buff->buffer);
		new_node = ft_lstnew(line);
		ft_lstadd_front(history, new_node);
	}
}

void	exec_up_arrow(t_input *buff, t_list *history)
{
	size_t	len;

	if (buff->pos == NULL)
	{
		len = ft_strlen(buff->buffer) + 1;
		ft_memcpy(buff->backup, buff->buffer, len);
		buff->pos = history;
	}
	else if (buff->pos->next != NULL)
		buff->pos = buff->pos->next;
	len = ft_strlen(buff->pos->content) + 1;
	ft_memcpy(buff->buffer, buff->pos->content, len);
}

void	exec_down_arrow(t_input *buff)
{
	size_t	len;

	if (buff->pos->previous != NULL)
	{
		buff->pos = buff->pos->previous;
		len = ft_strlen(buff->pos->content) + 1;
		ft_memcpy(buff->buffer, buff->pos->content, len);
	}
	else if (buff->pos->previous == NULL)
	{
		len = ft_strlen(buff->backup) + 1;
		ft_memcpy(buff->buffer, buff->backup, len);
		buff->pos = NULL;
	}
}

void	change_input_str(int arrow, t_input *buff, t_list *history)
{
	char	*pwd_val;
	int		i;

	i = 0;
	pwd_val = NULL;
	pwd_val = get_env_value(g_global.env_list, "PWD");
	exec_termcap("dl");
	ft_putstr_fd(pwd_val, STDERR_FILENO);
	write(STDERR_FILENO, "$> ", 3);
	if (arrow == UP_ARROW && history)
		exec_up_arrow(buff, history);
	else if (arrow == DN_ARROW && buff->pos != NULL)
		exec_down_arrow(buff);
	while (buff->buffer[i])
	{
		write(STDIN_FILENO, &buff->buffer[i++], 1);
		move_cursor(RIGHT);
	}
	// ft_putstr_fd(buff->buffer, 1); // should write characters by characters and save cursor position when newline
	buff->i = ft_strlen(buff->buffer);
}
