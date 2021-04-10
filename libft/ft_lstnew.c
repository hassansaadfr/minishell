/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:53:29 by axaidan           #+#    #+#             */
/*   Updated: 2021/04/10 11:53:06 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->content = content;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
