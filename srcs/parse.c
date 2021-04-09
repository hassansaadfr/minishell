/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:34:20 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 12:59:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**parse_cmd(char *splitted)
{
	char	**splitted_cmd;

	splitted_cmd = ft_split(splitted, ' ');
	return (splitted_cmd);
}

char			***parse(char *cmd)
{
	int		i;
	char	**splitted;
	char	***cmd_list;
	int		size;

	i = 0;
	splitted = ft_split(cmd, ';');						// NEEDS PROTECTION
//	if (splitted = ft_split(cmd, ';'))					
//	{
		size = get_strarr_size(splitted);
		cmd_list = malloc(sizeof(char*) * (size + 1));	// NEEDS PROTECTION
//		if (cmd_list)
//		{
			cmd_list[size] = NULL;
			while (splitted[i])
			{
				cmd_list[i] = parse_cmd(splitted[i]);
				i++;
			}
//		}
//	}
	free_split(splitted);
	return (cmd_list);
}
