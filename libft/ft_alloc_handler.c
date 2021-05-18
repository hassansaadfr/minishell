/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:01:47 by user42            #+#    #+#             */
/*   Updated: 2021/05/15 17:11:49 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0, NULL, 0);
	return (ptr);
}

void			ft_free_ptr(void **addr)
{
	ft_alloc_mem(0, 0, addr, 0);
}

void			ft_exit_free(int exit_code)
{
	ft_alloc_mem(0, 1, NULL, exit_code);
}
