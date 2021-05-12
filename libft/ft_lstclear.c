/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:49:30 by axaidan           #+#    #+#             */
/*   Updated: 2021/05/12 14:37:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*previous;

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		previous = current;
		current = current->next;
		printf("EXIT_freeing\t-\taddr\t= %p\n", previous->content);
		(*del)(previous->content);
		free(previous);
	}
	*lst = NULL;
}
