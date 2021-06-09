#include "libft.h"

static int	count_chars(long n)
{
	int	chars;

	if (n == 0)
		return (1);
	if (n < 0)
		chars = 1;
	else
		chars = 0;
	while (n)
	{
		n /= 10;
		chars++;
	}
	return (chars);
}

static void	make_str(char *str, long n, int *i)
{
	if (n < 0)
	{
		n = -n;
		str[(*i)++] = '-';
	}
	if (n >= 10)
	{
		make_str(str, n / 10, i);
		str[(*i)++] = n % 10 + '0';
	}
	if (n < 10)
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int x)
{
	long	n;
	char	*str;
	int		chars;
	int		i;

	n = x;
	chars = count_chars(n);
	str = ft_alloc(sizeof(char) * (chars + 1));
	i = 0;
	make_str(str, n, &i);
	str[chars] = '\0';
	return (str);
}
