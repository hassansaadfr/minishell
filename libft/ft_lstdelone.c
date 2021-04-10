/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:08:28 by axaidan           #+#    #+#             */
/*   Updated: 2021/04/10 15:05:18 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *elem, void (*del)(void *))
{
	if (del == NULL || elem == NULL)
		return ;
	if (elem->previous)
		elem->previous->next = elem->next;
	if (elem->next)
		elem->next->previous = elem->previous;
	(*del)(elem->content);
	free(elem);
}
