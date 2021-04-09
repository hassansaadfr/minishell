/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:40:42 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 22:17:10 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_strarr_size(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int		handle_errno(int err, char *binary, char *arg)
{
	if (err != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": ", 2);
		if (err != E2BIG)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
	}
	return (errno);
}
