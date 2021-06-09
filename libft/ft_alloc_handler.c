#include "libft.h"

void	*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0, NULL, 0);
	return (ptr);
}

void	ft_free_ptr(void **addr)
{
	ft_alloc_mem(0, 0, addr, 0);
}

void	ft_exit_free(int exit_code)
{
	ft_alloc_mem(0, 1, NULL, exit_code);
}
