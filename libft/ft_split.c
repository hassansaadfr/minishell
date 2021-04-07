/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:15:42 by axaidan           #+#    #+#             */
/*   Updated: 2020/11/18 15:04:30 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
			if (!(tab[j++] = malloc(sizeof(char) * (len + 1))))
			{
				free_split(tab);
				return (NULL);
			}
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
	if (!(tab = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	if (!(tab = alloc_words(s, c, tab)))
		return (NULL);
	tab = copy_words(s, c, tab);
	tab[words] = NULL;
	return (tab);
}
