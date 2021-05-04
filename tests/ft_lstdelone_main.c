#include "libft.h"
#include <stdio.h>

void	display_lst(t_list *hist)
{
	int		i;
	t_list	*last;


	last = ft_lstlast(hist);
	i = 0;
	printf("a l'endroit\n");
	while (hist)
	{
        printf("%d\tcur: %p\t\"%10.10s\"\tprv: %15p\tnxt: %15p\n", i++, hist,
            (char*)hist->content, hist->previous, hist->next);
		hist = hist->next;
	}
	printf("a l'envers\n");
	while (last)
	{
		printf("%d\tcur: %p\t\"%10.10s\"\tprv: %15p\tnxt: %15p\n", i++, last,
			(char*)last->content, last->previous, last->next);
		last = last->previous;
	}
	printf("fini\n");
}


void	create_list(t_list **lst)
{
	ft_lstadd_back(lst, ft_lstnew(ft_strdup("1")));
	ft_lstadd_back(lst, ft_lstnew(ft_strdup("2")));
	ft_lstadd_back(lst, ft_lstnew(ft_strdup("3")));
	ft_lstadd_back(lst, ft_lstnew(ft_strdup("4")));
}

void	testlst()
{
	t_list	*lst;

	lst = NULL;
	create_list(&lst);
	display_lst(lst);
	ft_lstdelone(&lst->next->next, free);
	ft_putstr_fd("+++++++\n", 0);
	display_lst(lst);
	ft_lstclear(&lst, free);
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
