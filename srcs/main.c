/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:43:29 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/07 13:57:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	ft_putstr_fd("minishell> ", 1);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret_gnl;

	(void)argc;
	(void)argv;
	(void)envp;
	ret_gnl = 1;
	line = NULL;
	while (ret_gnl > 0)
	{
		prompt();
		ret_gnl = get_next_line(1, &line);
		free(line);
	}
	return (1);
}
