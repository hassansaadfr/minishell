/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:43:04 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/30 15:55:38 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <string.h>
#include <limits.h>

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

void			*ft_alloc_mem(size_t size, int done)
{
	static t_list	*pointers = NULL;
	void			*ptr;

	if (done == 1)
		ft_lstclear(&pointers, free);
	ptr = malloc(size);
	if (ptr == NULL)
		exit_gracefully(&pointers, errno);
	else
		ft_lstadd_back(&pointers, ft_lstnew_alloc(ptr, &pointers));
	return (ptr);
}

void			*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0);
	return (ptr);
}

void			*ft_free(void)
{
	void	*ptr;

	ptr = ft_alloc_mem(0, 1);
}

// static t_list	*ft_lstnew_alloc(void *content, int *crash)
// {
// 	t_list	*new;

// 	if (!(new = malloc(sizeof(t_list))))
// 	{
// 		*crash += 1;
// 		return (NULL);
// 	}
// 	new->content = content;
// 	new->previous = NULL;
// 	new->next = NULL;
// 	return (new);
// }

// void			*ft_alloc(size_t size)
// {
// 	static t_list	*pointers = NULL;
// 	t_list			*new_node;
// 	static int		crash = 0;
// 	void			*ptr;

// 	new_node = NULL;
// 	if (crash)
// 		return (NULL);
// 	ptr = malloc(size);
// 	if (ptr == NULL)
// 	{
// 		ft_lstclear(&pointers, free);
// 		crash = 1;
// 		// return (NULL);
// 	}
// 	else
// 	{
// 		new_node = ft_lstnew_alloc(ptr, &crash);
// 		if (new_node != NULL)
// 			ft_lstadd_back(&pointers, new_node);
// 		else
// 		{
// 			ft_lstclear(&pointers, free);
// 			return (NULL);
// 		}
// 	}
// 	return (ptr);
// }
