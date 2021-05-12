/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:01:47 by user42            #+#    #+#             */
/*   Updated: 2021/05/12 17:03:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0, NULL);
	return (ptr);
}

void			ft_free_ptr(void **addr)
{
	ft_alloc_mem(0, 0, addr);
}

void			ft_exit_free(void)
{
	ft_alloc_mem(0, 1, NULL);
}
