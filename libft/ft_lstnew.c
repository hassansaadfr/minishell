#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ft_alloc(sizeof(t_list));
	new->content = content;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
