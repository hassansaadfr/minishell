#include <stdlib.h>
#include "../libft/libft.h"
#include <stdio.h>

int    main(void)
{
	t_list    *lst = NULL;
	t_list    *tmp;
	char    *str;

	char    *str1;
	char    *str2;
	char    *str3;

	str1 = ft_alloc(sizeof(char) * 5);
	str2 = ft_alloc(sizeof(char) * 5);
	str3 = ft_alloc(sizeof(char) * 5);
	ft_exit_free();
	ft_strlcpy(str1, "str1", 5);
	ft_strlcpy(str2, "str2", 5);
	ft_strlcpy(str3, "str3", 5);
	str = ft_strdup("hello");
	tmp = ft_lstnew(str);
	ft_lstadd_back(&lst, tmp);
	ft_free_ptr((void**)&str3);
	ft_free_ptr((void**)&str1);
	ft_free_ptr((void**)&str2);
	return (0);
}
