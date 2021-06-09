#include "libft.h"

void	*free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_free_ptr((void **)&str[i]);
		i++;
	}
	ft_free_ptr((void **)&str);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	state;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		state = 0;
		while (s[i] && s[i] != c)
		{
			state = 1;
			i++;
		}
		if (state == 1)
			words++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (words);
}

static char	**alloc_words(char const *s, char c, char **tab)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		if (len)
		{
			tab[j] = ft_alloc(sizeof(char) * (len + 1));
			j++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (tab);
}

static char	**copy_words(char const *s, char c, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] != c)
			tab[j][k++] = s[i++];
		if (k)
		{
			tab[j][k] = '\0';
			j++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = ft_alloc(sizeof(char *) * (words + 1));
	tab = alloc_words(s, c, tab);
	if (tab == NULL)
		return (NULL);
	tab = copy_words(s, c, tab);
	tab[words] = NULL;
	return (tab);
}
