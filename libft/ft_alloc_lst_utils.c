/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_lst_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:01:53 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/05/15 14:08:13 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_malloc_err(size_t size)
{
	static int current = 0;
	static int limit = -1;

	if (!DEBUG_MALLOC)
		return (malloc(size));
	if (limit == -1)
		limit = ft_atoi(getenv("LIMIT"));
	if (current++ < limit)
		return (malloc(size));
	else
	{
		write(1, "limit was set to ", 18);
		ft_putnbr_fd(limit, 1);
		ft_putchar_fd('\n', 1);
		return (NULL);
	}
}

void			exit_gracefully(t_list **arr_ptr, int err)
{
	if (errno)
		ft_putstr_fd(strerror(err), STDERR_FILENO);
	ft_clearallocs(arr_ptr, free);
	exit(0);
}

t_list			*ft_lstnew_alloc(void *content, t_list **arr_ptr)
{
	t_list	*new;

	errno = 0;
	new = ft_malloc_err(sizeof(t_list));
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

void			ft_lstdelnode(t_list **elem, void (*del)(void *))
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

void			ft_clearallocs(t_list **lst, void (*del)(void*))
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
		(*del)(previous->content);
		free(previous);
	}
	*lst = NULL;
}
