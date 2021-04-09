#include "minishell.h"

int		exec_from_builtins(char **argv, char **envp)
{
	/*
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
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(argv, envp));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (env(envp));
	return (0);
}

int     is_builtin(char **argv)
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
        //return (builtin_cd(argv, envp));
		return (1);
    if (ft_strncmp(argv[0], "env", 4) == 0)
        //return (env(envp));
		return (1);
    return (0);
}

