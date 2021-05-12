/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:20:18 by axaidan           #+#    #+#             */
/*   Updated: 2020/11/10 15:47:44 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_chars(long n)
{
	int	chars;

	if (n == 0)
		return (1);
	chars = (n < 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		chars++;
	}
	return (chars);
}

static void		make_str(char *str, long n, int *i)
{
	if (n < 0)
	{
		n = -n;
		str[(*i)++] = '-';
	}
	if (n >= 10)
	{
		make_str(str, n / 10, i);
		str[(*i)++] = n % 10 + '0';
	}
	if (n < 10)
		str[(*i)++] = n + '0';
}

char			*ft_itoa(int x)
{
	long	n;
	char	*str;
	int		chars;
	int		i;

	n = x;
	chars = count_chars(n);
	if (!(str = ft_alloc(sizeof(char) * (chars + 1))))
		return (NULL);
	i = 0;
	make_str(str, n, &i);
	str[chars] = '\0';
	return (str);
}
