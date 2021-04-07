/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:52:29 by axaidan           #+#    #+#             */
/*   Updated: 2020/11/10 16:09:42 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t					i;
	const unsigned char		*cp_src;
	unsigned char			*cp_dest;

	cp_src = src;
	cp_dest = dest;
	i = 0;
	while (i < n && cp_src[i] != (unsigned char)c)
	{
		cp_dest[i] = cp_src[i];
		i++;
	}
	if (i < n && cp_src[i] == (unsigned char)c)
	{
		cp_dest[i] = cp_src[i];
		i++;
		return (dest + i);
	}
	return (NULL);
}
