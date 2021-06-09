#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*temp;

	temp = s;
	i = 0;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}
