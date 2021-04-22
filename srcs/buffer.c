#include "minishell.h"

char    read_key(void)
{
    int     bytes_read;
    char    c;

    while ((bytes_read = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (bytes_read == -1 && errno != EAGAIN)
        {
            ft_putstr_fd("error -- read(2)\r\n", STDERR_FILENO);
            exit(1);
        }
    }
    return (c);
}

int    process_key(t_buff *buff)
{
    char    c;

    c = read_key();
	if (c == ESCAPE)
		return (arrow_value());
	else if (c == DELETE)
		delete_char(buff);
    else if (ft_isprint(c))
        write(STDIN_FILENO, &c, 1);
    return (c);
}

int		expand_buffers(t_buff *buff)
{
	(buff->factor)++;
	buff->buffer = ft_realloc(buff->buffer, INPUT_MAX * (buff->factor - 1),
		INPUT_MAX * buff->factor);
	buff->backup = ft_realloc(buff->backup, INPUT_MAX * (buff->factor - 1),
		INPUT_MAX * buff->factor);
	if (buff->backup == NULL || buff->buffer == NULL)
	{
		free(buff->buffer);
		free(buff->backup);
		return (1);
	}
	return (0);
}

int		write_buffer(int *stop, t_buff *buff, t_list *history)
{
    int		c;

    buff->i = 0;
    c = '\0';
    while (c != ENTER && *stop == 0)
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
		else if (is_ctrl_keys(c, stop, buff, history))
			;
    }
    write(STDIN_FILENO, "\r\n", 2);
	return (*stop);
}

/*
void    print_buffer(t_buff *buff)
{
    if (buff->buffer[0] != '\0')
    {
        ft_putstr_fd(buff->buffer, STDIN_FILENO);
        write(STDIN_FILENO, "\r\n", 2);
    }
}
*/
