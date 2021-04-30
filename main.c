#include "libft.h"

int	main(void)
{
	char	*str;

	str = ft_alloc(sizeof(char) * 3);
	str[0] = '1';
	str[1] = '2';
	str[2] = 0;
	ft_putendl_fd(str, STDOUT_FILENO);
	// ft_free_ptr(str);
	ft_exit_free();
	ft_putendl_fd(str, STDOUT_FILENO);
	return (0);
}
