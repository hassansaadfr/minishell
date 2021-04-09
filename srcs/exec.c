/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:30:24 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 16:54:19 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char **argv, char **envp)
{
	// TODO ALL FUNCTIONS
	/*
	   if (ft_strncmp(argv[0], "pwd", 4) == 0)
	   return (builtin_pwd());
	   if (ft_strncmp(argv[0], "echo", 5) == 0)
	   return (builtin_echo());
	   if (ft_strncmp(argv[0], "unset", 6) == 0)
	   return (builtin_unset());
	   if (ft_strncmp(argv[0], "export", 8) == 0)
	   return (builtin_export());
	   if (ft_strncmp(argv[0], "exit", 5) == 0)
	   return (builtin_exit());
	 */
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(argv, envp));
	if (ft_strncmp(argv[0], "env", 4) == 0)
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
		ret = waitpid(0, &status, 0); 		//	-1 ON ERROR
	}
	else if (pid == 0)
	{
		// ENFANT
		ret = execve(path, args, envp);		//	-1 ON ERROR
		free_split(args);
	}
	else
		printf("ERROR - fork\n");
	return (0);
}

static int	search_bin(char **cmd, char **envp)
{
	char			**bin_paths;
	char			*env_path;
	char			*checked_path;
	int				i;
	int				ret;
	struct stat		stat_buff;

	env_path = getenv("PATH");				//	NULL IF NO MATCH
	bin_paths = ft_split(env_path, ':');	//	NULL IF ALLOC REFUSED
	i = 0;
	ret = -1;
	// CREATE int is_path() FUNCTION WRAPPING if / else if
	if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		checked_path = create_full_path(getenv("PWD"), cmd[0]);
		ret = stat(checked_path, &stat_buff);
	}
	else if (ft_strncmp(cmd[0], "/", 1) == 0)
	{
		checked_path = cmd[0];
		ret = stat(checked_path, &stat_buff);
	}
	else
	{
		while (bin_paths[i] && ret != 0)
		{
			checked_path = create_full_path(bin_paths[i], cmd[0]);
			ret = stat(checked_path, &stat_buff);
			if (ret)
				free(checked_path);
			i++;
		}
	}
	if (ret == 0)
	{
		exec_bin(checked_path, cmd, envp);
		free(checked_path);
	}
	free_split(bin_paths);
	return (1);
}

int		exec(char ***cmds, char **envp)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (!is_builtin(cmds[i], envp))
			search_bin(cmds[i], envp);
		i++;
	}
	free_cmds(cmds);
	return (0);
}
