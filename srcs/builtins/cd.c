/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:48:17 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 14:59:16 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	update_pwd(char *path, char **envp)
{
	int		i;
	char	buff[PATH_MAX];
	char	*final_path;

	i = 0;
	errno = 0;
	path = ft_strjoin("/", path);
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	if (getcwd(buff, PATH_MAX) != NULL)
	{
		final_path = ft_strjoin("PWD=", buff);
		envp[i] = ft_strdup(final_path);
		free(final_path);
	}
	else
	{
		printf("minishell: %s\n", strerror(errno));
		return (0);
	}
	free(path);
	return (1);
}

int			builtin_cd(char **argv, char **env)
{
	int		ret;

	(void)env;
	errno = 0;
	ret = chdir(argv[1]);
	if (ret == 0)
	{
		if (update_pwd(argv[1], env))
			return (1);
		return (0);
	}
	else
		printf("minishell: %s\n", strerror(errno));
	return (ret);
}
