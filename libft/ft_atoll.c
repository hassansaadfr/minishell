/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:23:29 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/05/24 19:02:20 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		is_overflow(long long n, long long sign, int *overflow)
{
	if (n < 0 && sign == 1)
		*overflow = 1;
	else if (n < 0 && sign == -1 && n > LONG_MIN)
		*overflow = 1;
}

long long		ft_atoll(const char *nptr, int *overflow)
{
	long long int	n;
	size_t			i;
	long long int	sign;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' ||
			nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	n = 0;
	while ((nptr[i] >= '0' && nptr[i] <= '9') && *overflow == 0)
	{
		n = n * 10 + nptr[i] - '0';
		is_overflow(n, sign, overflow);
		i++;
	}
	return (sign * n);
}
