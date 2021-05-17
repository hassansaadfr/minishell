/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:01:51 by user42            #+#    #+#             */
/*   Updated: 2021/05/17 14:41:44 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**find_addr(t_list **lst, void *addr)
{
	t_list **node_addr;

	while (*lst)
	{
		if (addr == (*lst)->content)
		{
			node_addr = lst;
			return (node_addr);
		}
		*lst = (*lst)->next;
	}
	return (NULL);
}

static void		*ft_free(t_list **pointers, void **addr)
{
	t_list			**tmp;
	t_list			*cursor;

	tmp = NULL;
	if (*pointers && *addr == (*pointers)->content)
		ft_lstdelnode(pointers, free);
	else
	{
		cursor = *pointers;
		tmp = find_addr(&cursor, *addr);
		if (tmp)
		{
			ft_lstdelnode(tmp, free);
			*addr = NULL;
		}
	}
	return (NULL);
}

void			*ft_alloc_mem(size_t size, int done, void **addr, int exit_code)
{
	static t_list	*pointers = NULL;
	void			*ptr;

	if (done == 1)
		exit_gracefully(&pointers, 0, exit_code);
	if (addr != NULL)
		return (ft_free(&pointers, addr));
	ptr = ft_malloc_err(size);
	if (ptr == NULL)
		exit_gracefully(&pointers, errno, 0);
	else
		ft_lstadd_back(&pointers, ft_lstnew_alloc(ptr, &pointers));
	return (ptr);
}
