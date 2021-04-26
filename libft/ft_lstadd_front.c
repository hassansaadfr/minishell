/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:57:31 by axaidan           #+#    #+#             */
/*   Updated: 2021/04/22 10:54:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	if (*alst)
		(*alst)->previous = new;
	new->next = *alst;
	new->previous = NULL;
	*alst = new;
}
