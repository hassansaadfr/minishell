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
