#include "libft.h"
#include <stdio.h>

void	testlst()
{
	t_list	*lst;
	t_list	*tmp;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("1")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("2")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("3")));

	char *str;
	ft_lstdelone(&lst->next->next, free);
	tmp = lst;
	printf("+++++++\n");
	// lst = *head;
	while (lst)
	{
		str = lst->content;
		printf("%s\n", str);
		lst = lst->next;
	}
	ft_lstclear(&tmp, free);
}

int	main(void)
{
	// char	*str;

	// str = ft_alloc(sizeof(char) * 3);
	// str[0] = '1';
	// str[1] = '2';
	// str[2] = 0;
	// ft_putendl_fd(str, STDOUT_FILENO);
	// // ft_free_ptr((void**)(&str));
	// ft_exit_free();
	// // str = NULL;
	// ft_putendl_fd(str, STDOUT_FILENO);
	testlst();
	return (0);
}
