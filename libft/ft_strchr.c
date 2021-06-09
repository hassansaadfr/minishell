#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == '\0' && (char)c != '\0')
		return (NULL);
	return ((char *)(s + i));
}
