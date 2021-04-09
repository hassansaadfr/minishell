/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:43:29 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 13:25:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret_gnl;


	(void)argc;
	(void)argv;
//	change_shlvl(envp);
	ret_gnl = 1;
	line = NULL;
	while (ret_gnl > 0)
	{
		prompt();
		ret_gnl = get_next_line(0, &line);
		if (*line)
			exec(parse(line), envp);
		free(line);
	}
	return (1);
}
