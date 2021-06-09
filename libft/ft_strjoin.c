#include "libft.h"

static int	len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*cat;

	if (!s1 || !s2)
		return (NULL);
	cat = ft_alloc(sizeof(char) * (len(s1) + len(s2) + 1));
	i = 0;
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		cat[i + j] = s2[j];
		j++;
	}
	cat[i + j] = '\0';
	return (cat);
}
