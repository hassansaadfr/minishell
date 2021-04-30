/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:12:52 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/30 16:13:07 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0, NULL);
	return (ptr);
}

void			ft_free_ptr(void *addr)
{
	ft_alloc_mem(0, 0, addr);
}

void			ft_exit_free(void)
{
	ft_alloc_mem(0, 1, NULL);
}
