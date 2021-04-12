/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:48:17 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/12 15:01:01 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_list *env_list)
{
	char	buff[PATH_MAX];
	char	*final_path;

	if (getcwd(buff, PATH_MAX) != NULL)
	{
		final_path = ft_strjoin("PWD=", buff);
		edit_env(env_list, final_path);
		return (1);
	}
	return (0);
}

int			builtin_cd(char **argv, t_list *env_list)
{
	int		ret;

	errno = 0;
	ret = 0;
	if (argv[1] && ft_strlen(argv[1]) > 0)
	{
		ret = chdir(argv[1]);
		if (get_strarr_size(argv) > 2)
			errno = E2BIG;
		if (ret == 0)
		{
			if (update_pwd(env_list))
				return (1);
			return (0);
		}
		handle_errno(errno, "cd", argv[1]);
	}
	return (ret);
}
