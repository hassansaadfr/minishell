/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:48:17 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/12 13:55:39 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	update_pwd(char *path, t_list *env_list)
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
		return (0);
	free(path);
	return (1);
}

int			builtin_cd(char **argv, t_list *env_list)
{
	int		ret;

	(void)env;
	errno = 0;
	ret = chdir(argv[1]);
	if (get_strarr_size(argv) > 2)
		errno = E2BIG;
	if (ret == 0)
	{
		if (update_pwd(argv[1], env_list))
			return (1);
		return (0);
	}
	handle_errno(errno, "cd", argv[1]);
	return (ret);
}
