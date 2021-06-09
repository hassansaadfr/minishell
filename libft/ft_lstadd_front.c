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
