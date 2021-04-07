/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:44:04 by axaidan           #+#    #+#             */
/*   Updated: 2020/11/10 17:46:43 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*pos;
	int			i;

	pos = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			pos = s + i;
		i++;
	}
	if (s[i] == '\0' && c != '\0' && pos == NULL)
		return (NULL);
	else if (c == '\0')
		return ((char*)(s + i));
	return ((char *)(pos));
}
