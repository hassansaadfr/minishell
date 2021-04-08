/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:30:24 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 15:15:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *cmd, char **envp)
{
	// TODO ALL FUNCTIONS
	/*
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
	 */
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (env(envp));
	return (0);
}

char		*create_full_path(char *bin_path, char *cmd)
{
	char 	*tmp;
	char	*s;

	s = ft_strjoin(bin_path, "/");
	tmp = s;
	s = ft_strjoin(s, cmd);
	free(tmp);
	return (s);
}

static int	exec_bin(char *path, char **args, char **envp)
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = fork();
	if (pid > 0)
	{
		// PARENT
		ret = waitpid(0, &status, 0); 
	}
	else if (pid == 0)
	{
		// ENFANT
		ret = execve(path, args, envp);
	}
	else
		printf("ERROR - fork\n");
	return (12098);
}

static int	search_bin(char **cmd, char **envp)
{
	char			**bin_paths;
	char			*env_path;
	char			*checked_path;
	int				i;
	int				ret;
	struct stat		stat_buff;

	env_path = getenv("PATH");
	bin_paths = ft_split(env_path, ':');
	i = 0;
	/*
	. ==> $PWD
	.. => $PWD - dernier '/' et ce qui suit
	*/
	if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		// CHEMIN RELATIF 
		checked_path = create_full_path(getenv("PWD"), cmd[0]); 
		ret = stat(checked_path, &stat_buff);
	}
	else if (ft_strncmp(cmd[0], "/", 1) == 0)
	{
		// CHEMIN ABSOLU
		checked_path = cmd[0]; 
		ret = stat(checked_path, &stat_buff);
	}
	else
	{
	// CHERCHER LE BINAIRE DANS $PATH
		while (bin_paths[i] && ret != 0)
		{
			checked_path = create_full_path(bin_paths[i], cmd[0]);
			ret = stat(checked_path, &stat_buff);
			//printf("checked_path[%d] : \"%s\"\n", i, checked_path);
			//printf("ret = %d\n", ret);
			//dbg_display_stat_buff(stat_buff);
			i++;
			// FREE (PATH)
		}
	}
	if (ret == 0)
		exec_bin(checked_path, cmd, envp);
	return (1);
}

int		exec(char ***cmds, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (!is_builtin(cmds[i][0], envp))
			search_bin(cmds[i], envp);
		i++;
	}
	return (0);
}
