/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:43:04 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/30 16:16:23 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <string.h>

static void		exit_gracefully(t_list **arr_ptr, int err)
{
	ft_putstr_fd(strerror(err), STDERR_FILENO);
	ft_lstclear(arr_ptr, free);
	exit(1);
}

static t_list	*ft_lstnew_alloc(void *content, t_list **arr_ptr)
{
	t_list	*new;

	errno = 0;
	new = malloc(sizeof(t_list));
	if (new == NULL)
		exit_gracefully(arr_ptr, errno);
	new->content = content;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

static t_list	*find_addr(t_list *lst, void *addr)
{
	while (lst)
	{
		if (addr == lst->content)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void			*ft_alloc_mem(size_t size, int done, void *addr)
{
	static t_list	*pointers = NULL;
	t_list			*tmp;
	void			*ptr;

	tmp = NULL;
	if (done == 1)
	{
		ft_lstclear(&pointers, free);
		return (NULL);
	}
	if (addr != NULL)
	{
		tmp = find_addr(pointers, addr);
		if (tmp)
			ft_lstdelone(tmp, free);
		return (NULL);
	}
	ptr = malloc(size);
	if (ptr == NULL)
		exit_gracefully(&pointers, errno);
	else
		ft_lstadd_back(&pointers, ft_lstnew_alloc(ptr, &pointers));
	return (ptr);
}
