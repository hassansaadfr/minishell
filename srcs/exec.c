/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:30:24 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 12:59:13 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *cmd)
{
	// TODO ALL FUNCTIONS
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (builtin_cd());
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (builtin_echo());
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (builtin_unset());
	if (ft_strncmp(cmd, "export", 8) == 0)
		return (builtin_export());
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (builtin_exit());
	if (ft_strncmp(cmd, "env", 5) == 0)
		return (builtin_env());
	return (0);
}

static int	exec_bin(char *path, char **cmd)
{
	(void)cmd;
	// TODO SEARCH IN PATH THE BINARY
	printf("Should execute %s\n", path);
	return (1);
}

int		exec(char ***cmds, char **envp)
{
	int		i;
	int		j;
	char	**path;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (!is_builtin(cmds[i][0]))
		{
			path = ft_strjoin(getenv("PATH"), cmds[i][0]);
			exec_bin(path, cmds[i]);
			free(path);
		}
		i++;
	}
}
