#include "minishell.h"

char		*create_full_path(char *bin_path, char *cmd)
{
	char 	*tmp;
	char	*s;

	s = ft_strjoin(bin_path, "/");
	// CHECK ft_strjoin() RETURN 
	tmp = s;
	s = ft_strjoin(s, cmd);
	// CHECK ft_strjoin() RETURN 
	free(tmp);
	return (s);
}

int	exec_bin(char *path, char **args, char **envp)
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
	if (is_path(cmd[0]))
		exec_from_path(cmd, envp);
	else
		exec_from_bins(cmd, envp);
	return (0);
}

int		exec(char ***cmds, char **envp)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (!is_builtin(cmds[i][0], envp))
			search_bin(cmds[i], envp);
		i++;
	}
	free_cmds(cmds);
	return (0);
}
