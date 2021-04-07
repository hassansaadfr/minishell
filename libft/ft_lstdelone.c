/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:08:28 by axaidan           #+#    #+#             */
/*   Updated: 2020/09/25 19:08:55 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *elem, void (*del)(void *))
{
	if (del == NULL || elem == NULL)
		return ;
	(*del)(elem->content);
	free(elem);
}
