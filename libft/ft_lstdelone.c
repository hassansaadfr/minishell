/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:08:28 by axaidan           #+#    #+#             */
/*   Updated: 2021/05/04 19:11:35 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** NULL-X-NULL		=> NULL				/// If NO prv and NO next ELEM = NULL
** NULL-X-0-NULL	=> NULL-0-NULL		/// if NO prv and next ELEM = next;
** NULL-0-X-NULL	=> NULL-0-NULL		/// if prv and NO next ELEM = prev;
** NULL-0-X-0-NULL	=> NULL-0-0-NULL 	/// if prev and next ELEM = prev;
*/

void	ft_lstdelone(t_list **elem, void (*del)(void *))
{
	t_list	*tmp;

	if (del == NULL || *elem == NULL)
		return ;
	tmp = *elem;
	if ((*elem)->previous == NULL && (*elem)->next == NULL)
		*elem = NULL;
	else if ((*elem)->previous == NULL && (*elem)->next != NULL)
	{
		*elem = (*elem)->next;
		(*elem)->previous = NULL;
	}
	else if ((*elem)->previous != NULL && (*elem)->next == NULL)
	{
		*elem = (*elem)->previous;
		(*elem)->next = NULL;
	}
	else if ((*elem)->previous != NULL && (*elem)->next != NULL)
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
	}
	del(tmp->content);
	free(tmp);
}
