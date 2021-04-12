/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:16:07 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/12 13:53:02 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *env_list)
{
	if (isatty(0))
	{
		ft_putstr_fd(get_env(env_list, "PWD")->content, 2);
		ft_putstr_fd("$> ", 2);
	}
}
