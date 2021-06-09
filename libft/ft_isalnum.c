#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && '9' >= c)
		|| (c >= 'a' && 'z' >= c)
		|| (c >= 'A' && 'Z' >= c));
}
