/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:17:05 by axaidan           #+#    #+#             */
/*   Updated: 2020/11/10 16:48:34 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = ft_strlen((const char*)dest);
	len_s = ft_strlen(src);
	if (size > 0)
	{
		i = 0;
		while (len_d + i < size - 1 && src[i])
		{
			dest[len_d + i] = src[i];
			i++;
		}
		dest[len_d + i] = '\0';
	}
	if (len_d < size)
		return (len_d + len_s);
	return (size + len_s);
}
