#include "libft.h"

static char	*join_str(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	stot_len;
	char	*remaining;

	s1_len = 0;
	s2_len = 0;
	if (!s1 && !s2)
		return (0);
	if (s1)
		s1_len = ft_strlen((char *)s1);
	if (s2)
		s2_len = ft_strlen((char *)s2);
	stot_len = s1_len + s2_len + 1;
	remaining = ft_alloc(sizeof(char) * stot_len);
	if (!remaining)
		return (0);
	ft_memmove(remaining, s1, s1_len);
	ft_memmove(remaining + s1_len, s2, s2_len);
	remaining[stot_len - 1] = '\0';
	ft_free_ptr((void **)&s1);
	return (remaining);
}

static int	get_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_rest(char *buff)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buff)
		return (0);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		ft_free_ptr((void **)&buff);
		return (0);
	}
	remaining = ft_alloc(sizeof(char) * ((ft_strlen(buff) - i) + 1));
	i++;
	while (buff[i])
		remaining[j++] = buff[i++];
	remaining[j] = '\0';
	ft_free_ptr((void **)&buff);
	return (remaining);
}

static char	*get_correct_line(char *str)
{
	int		i;
	char	*remaining;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	remaining = ft_alloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		remaining[i] = str[i];
		i++;
	}
	remaining[i] = '\0';
	return (remaining);
}

int	get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*rem[4096];
	int				reader;

	reader = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buff = ft_alloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!get_nl(rem[fd]) && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			ft_free_ptr((void **)&buff);
			return (-1);
		}
		buff[reader] = '\0';
		rem[fd] = join_str(rem[fd], buff);
	}
	ft_free_ptr((void **)&buff);
	*line = get_correct_line(rem[fd]);
	rem[fd] = get_rest(rem[fd]);
	if (reader == 0)
		return (0);
	return (1);
}
