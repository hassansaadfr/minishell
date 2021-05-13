#include "minishell.h"

void	display_history(t_list *hist)
{
	int		i;

	printf("\n");
	i = 0;
	while (hist)
	{
		printf("%d\tcur: %p\t\"%10.10s\"\tprv: %p\tnxt: %p\n", i++, hist,
			hist->content, hist->previous, hist->next);
		hist = hist->next;
	}
}

int		add_to_history(t_input *buff, t_list **history)
{
	char	*line;
	t_list	*new_node;

	if (not_empty(buff->buffer))
	{
		line = ft_strdup(buff->buffer);
		if (line == NULL)
			return (1);
		new_node = ft_lstnew(line);
		if (new_node == NULL)
		{
			free(line);
			return (1);
		}
		ft_lstadd_front(history, new_node);
	}
	return (0);
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
	t_list	*tmp;
	char	*pwd_val;

	pwd_val = NULL;
	tmp = get_env(g_global.env_list, "PWD");
	if (tmp)
		pwd_val = ((t_env*)tmp->content)->value;
	exec_termcap("dl");
	ft_putstr_fd(pwd_val, STDERR_FILENO);
	write(STDERR_FILENO, "$> ", 3);
	if (arrow == UP_ARROW && history)
		exec_up_arrow(buff, history);
	else if (arrow == DN_ARROW && buff->pos != NULL)
		exec_down_arrow(buff);
	ft_putstr_fd(buff->buffer, 1);
	buff->i = ft_strlen(buff->buffer);
}
