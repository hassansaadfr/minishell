/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:18:27 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/12 14:15:04 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env(t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = env_list->next;
	}
	return (1);
}
