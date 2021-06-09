/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:55:04 by axaidan           #+#    #+#             */
/*   Updated: 2021/06/08 00:08:37 by hsaadaou         ###   ########.fr       */
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
			ft_free_ptr((void **)&line);
			ft_free_ptr((void **)&remaining);
			*line = NULL;
			return (NULL);
		}
		ft_free_ptr((void **)&remaining);
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
		ft_free_ptr((void **)&temp_line);
		ft_free_ptr((void **)&remaining);
		return (NULL);
	}
	if (remaining && !(newline_pos))
		ft_free_ptr((void **)&remaining);
	ft_free_ptr((void **)&temp_line);
	return (nl_return(newline_pos, line, remaining));
}

int		get_next_line(int fd, char **line)
{
	static char	*remaining = NULL;
	char		buff[BUFFER_SIZE + 1];
	int			bytes_read;

	if (check_errors(fd, line) || !(*line = ft_strdup("")))
	{
		ft_free_ptr((void **)&remaining);
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
				ft_free_ptr((void **)&line);
			return (bytes_read);
		}
		buff[bytes_read] = '\0';
	}
	return (1);
}
