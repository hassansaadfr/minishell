/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:15:42 by axaidan           #+#    #+#             */
/*   Updated: 2021/05/14 15:42:28 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
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

static char		**alloc_words(char const *s, char c, char **tab)
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
			tab[j++] = ft_alloc(sizeof(char) * (len + 1));
		while (s[i] && s[i] == c)
			i++;
	}
	return (tab);
}

static char		**copy_words(char const *s, char c, char **tab)
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

char			**ft_split(char const *s, char c)
{
	int		words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!(tab = ft_alloc(sizeof(char *) * (words + 1))))
		return (NULL);
	if (!(tab = alloc_words(s, c, tab)))
		return (NULL);
	tab = copy_words(s, c, tab);
	tab[words] = NULL;
	return (tab);
}
