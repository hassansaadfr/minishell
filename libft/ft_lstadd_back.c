/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:00:23 by axaidan           #+#    #+#             */
/*   Updated: 2021/05/16 14:51:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->previous = temp;
}
*/
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->previous = temp;
	new->next = NULL;
}
