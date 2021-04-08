/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:48:17 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 17:15:56 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(char *path, char **envp)
{
	int		i;
	char	**splitted;

	i = 0;
	path = ft_strjoin("/", path);
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	splitted = ft_split(envp[i], '=');
	splitted[0] = ft_strjoin(splitted[0], "=");
	splitted[1] = ft_strjoin(splitted[1], path);
	envp[i] = ft_strjoin(splitted[0], splitted[1]);
	free(splitted[0]);
	free(splitted[1]);
	free(splitted);
	free(path);
	return (1);
}

int		builtin_cd(char **argv, char **env)
{
	int		ret;

	(void)env;

	ret = chdir(argv[1]);
	if (ret == 0)
	{
		update_pwd(argv[1], env);
		return (1);
	}
	else
		printf("minishell: cd: %s: No such file or directory\n", argv[1]);
	return (ret);
}
