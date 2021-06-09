#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	alloc = ft_alloc(size * nmemb);
	ft_bzero(alloc, size * nmemb);
	return (alloc);
}
