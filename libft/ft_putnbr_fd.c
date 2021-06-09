#include "libft.h"

void	ft_putnbr_fd(int x, int fd)
{
	long	n;
	char	c;

	if (fd < 0)
		return ;
	n = x;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}
