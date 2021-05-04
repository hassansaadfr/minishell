/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:08:28 by axaidan           #+#    #+#             */
/*   Updated: 2021/05/04 16:38:07 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **elem, void (*del)(void *))
{
	t_list	*tmp;

	tmp = NULL;
	if (del == NULL || elem == NULL)
		return ;
	if ((*elem)->previous)
		(*elem)->previous->next = (*elem)->next;
	else
		tmp = (*elem)->next;
	if ((*elem)->next)
		(*elem)->next->previous = (*elem)->previous;
	(*del)((*elem)->content);
	free(*elem);
	// if (tmp)
		*elem = tmp;
}

// NULL-X-NULL			=> NULL
// NULL-X-0-NULL		=> NULL-0-NULL
// NULL-0-X-NULL		=> NULL-0-NULL		/// SIZE ?
// NULL-0-X-0-NULL		=> NULL-0-0-NULL 	/// OK
