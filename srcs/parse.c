/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:34:20 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 12:26:37 by hsaadaou         ###   ########.fr       */
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
	splitted = ft_split(cmd, ';');
	size = get_strarr_size(splitted);
	cmd_list = malloc(sizeof(char*) * (size + 1));
	cmd_list[size] = 0;
	while (splitted[i])
	{
		cmd_list[i] = parse_cmd(splitted[i]);
		i++;
	}
	return (cmd_list);
}
