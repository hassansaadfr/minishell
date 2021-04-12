/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:16:07 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/12 14:46:37 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *env_list)
{
	t_list	*tmp;
	char	*env_val;

	env_val = NULL;
	tmp = get_env(env_list, "PWD");
	if (!tmp)
		return ;
	env_val = ft_strchr(tmp->content, '=') + 1;
	if (isatty(0))
	{
		ft_putstr_fd(env_val, 2);
		ft_putstr_fd("$> ", 2);
	}
}
