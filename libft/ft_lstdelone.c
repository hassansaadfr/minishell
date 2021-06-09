#include "libft.h"
#include <stdio.h>

static void	rearrange(t_list **elem, void (*del)(void *))
{
	t_list	*tmp;

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
	if (del)
	{
		del(tmp->content);
		ft_free_ptr((void **)&tmp);
	}
}

void	ft_lstdelone(t_list **elem, void (*del)(void *))
{
	if (*elem)
		rearrange(elem, del);
}
