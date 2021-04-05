/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:51:00 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:59 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

static int		ft_addition(int a, int b)
{
	return (a + b);
}

Test(misc, failing) {
    cr_assert(ft_addition(1, 1) == 2);
}

Test(misc, passing) {
    cr_assert(ft_addition(1, 1) == 2);
}
