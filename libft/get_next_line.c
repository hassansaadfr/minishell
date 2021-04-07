/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:55:04 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/16 15:43:06 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_errors(int fd, char **line)
{
	char	buff_test[1];

	if (fd < 0 || line == NULL || (read(fd, buff_test, 0) < 0)
			|| BUFFER_SIZE < 1)
		return (1);
	return (0);
}

char	*nl_return(char *newline_pos, char **line, char *remaining)
{
	if (newline_pos == NULL)
		return (NULL);
	else
	{
		if (!(newline_pos = ft_strdup(newline_pos + 1)))
		{
			free(*line);
			free(remaining);
			*line = NULL;
			return (NULL);
		}
		free(remaining);
		return (newline_pos);
	}
}

char	*find_nl(char *remaining, char **line, char *buff)
{
	char	*temp_line;
	char	*to_parse;
	char	*newline_pos;

	to_parse = (remaining == NULL) ? buff : remaining;
	temp_line = *line;
	if ((newline_pos = ft_strchr(to_parse, '\n')))
		*newline_pos = '\0';
	if (!(*line = ft_strjoin(*line, to_parse)))
	{
		free(temp_line);
		free(remaining);
		return (NULL);
	}
	if (remaining && !(newline_pos))
		free(remaining);
	free(temp_line);
	return (nl_return(newline_pos, line, remaining));
}

int		get_next_line(int fd, char **line)
{
	static char	*remaining = NULL;
	char		buff[BUFFER_SIZE + 1];
	int			bytes_read;

	if (check_errors(fd, line) || !(*line = ft_strdup("")))
	{
		free(remaining);
		return (-1);
	}
	if (!remaining)
		ft_memset(buff, 0, BUFFER_SIZE + 1);
	while (!(remaining = find_nl(remaining, line, buff)))
	{
		if (*line == NULL)
			return (-1);
		if ((bytes_read = read(fd, buff, BUFFER_SIZE)) <= 0)
		{
			if (bytes_read < 0)
				free(*line);
			return (bytes_read);
		}
		buff[bytes_read] = '\0';
	}
	return (1);
}
