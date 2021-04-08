/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:16:07 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 16:16:17 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	if (isatty(0))
	{
		ft_putstr_fd(getenv("PWD"), 2);
		ft_putstr_fd("$> ", 2);
	}
}
