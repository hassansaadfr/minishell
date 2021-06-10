#include "minishell.h"

char	read_key(void)
{
	int		bytes_read;
	char	c;

	bytes_read = 0;
	while (bytes_read != 1)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read == -1 && errno != EAGAIN)
		{
			ft_putstr_fd("error -- read(2)\n", STDERR_FILENO);
			exit(1);
		}
	}
	return (c);
}

int	process_key(t_input *buff)
{
	char	c;

	c = read_key();
	if (c == ESCAPE)
		return (arrow_value());
	else if (c == DELETE)
		delete_char(buff);
	else if (ft_isprint(c))
		write(STDIN_FILENO, &c, 1);
	return (c);
}

int	expand_buffers(t_input *buff)
{
	(buff->factor)++;
	buff->buffer = ft_realloc(buff->buffer,
			(size_t)INPUT_MAX * (buff->factor - 1), INPUT_MAX * buff->factor);
	buff->backup = ft_realloc(buff->backup,
			(size_t)INPUT_MAX * (buff->factor - 1), INPUT_MAX * buff->factor);
	return (0);
}

void	write_buffer(t_input *buff, t_list *history)
{
	int		c;

	c = '\0';
	while (c != ENTER)
	{
		c = process_key(buff);
		if (buff->i == (INPUT_MAX * buff->factor) - 1)
		{
			if (expand_buffers(buff))
				return (1);
		}
		if (ft_isprint(c))
		{
			buff->buffer[buff->i++] = c;
			buff->buffer[buff->i] = '\0';
		}
		else if (c == UP_ARROW || c == DN_ARROW)
			change_input_str(c, buff, history);
		else if (is_ctrl_keys(c, buff, history))
			;
	}
	write(STDIN_FILENO, "\n", 2);
}
