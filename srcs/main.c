/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:43:29 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/07 16:45:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	if (isatty(0))
		ft_putstr_fd("minishell> ", 2);
}

void	env(char **envp)
{
	while (*envp)
		printf("%s\n", *envp++);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret_gnl;

	(void)argc;
	(void)argv;
	ret_gnl = 1;
	line = NULL;
	while (ret_gnl > 0)
	{
		prompt();
		ret_gnl = get_next_line(0, &line);
		if (ft_strncmp(line, "env", 4) == 0)
			env(envp);
		free(line);
	}
	return (1);
}
