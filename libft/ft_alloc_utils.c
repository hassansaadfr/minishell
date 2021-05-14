/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:01:51 by user42            #+#    #+#             */
/*   Updated: 2021/05/14 13:45:22 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		exit_gracefully(t_list **arr_ptr, int err)
{
	if (errno)
		ft_putstr_fd(strerror(err), STDERR_FILENO);
	ft_lstclear(arr_ptr, free);
	exit(0);
}

void	ft_lstdelnode(t_list **elem, void (*del)(void *))
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

static t_list	*ft_lstnew_alloc(void *content, t_list **arr_ptr)
{
	t_list	*new;

	errno = 0;
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(content);
		exit_gracefully(arr_ptr, errno);
	}
	ft_bzero(new, sizeof(t_list));
	new->content = content;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

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

void			*ft_alloc_mem(size_t size, int done, void **addr)
{
	static t_list	*pointers = NULL;
	void			*ptr;

	if (done == 1)
		exit_gracefully(&pointers, 0);
	if (addr != NULL)
		return (ft_free(&pointers, addr));
	ptr = malloc(size);
	if (ptr == NULL)
		exit_gracefully(&pointers, errno);
	else
		ft_lstadd_back(&pointers, ft_lstnew_alloc(ptr, &pointers));
	return (ptr);
}
