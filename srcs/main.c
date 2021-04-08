/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:43:29 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 14:41:45 by user42           ###   ########.fr       */
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

int		env(char **envp)
{
	while (*envp)
		printf("%s\n", *envp++);
	return (1);
}

void change_shlvl(char **envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "SHLVL", 5) != 0)
		i++;
	if (envp[i])
		envp[i][6] = '8';
}


int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret_gnl;
	
	
	printf("MINISHELL LAUNCH\n");
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
