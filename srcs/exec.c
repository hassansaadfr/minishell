#include "minishell.h"

char		**list_to_array(t_list *env_list)
{
	t_list	*tmp;
	char	**out;
	int		size;
	int		i;

	i = 0;
	size = 0;
	tmp = env_list;
	if (!env_list)
		return (NULL);
	size = ft_lstsize(env_list);
	out = malloc(sizeof(char*) * (size + 1));
	if (!out)
		return (NULL);
	out[size] = 0;
	while (env_list)
	{
		out[i] = env_list->content;
		env_list = env_list->next;
		i++;
	}
	return (out);
}

/*
** TODO:
** - Check strjoin returns
*/

char		*create_full_path(char *bin_path, char *cmd)
{
	char	*tmp;
	char	*s;

	s = ft_strjoin(bin_path, "/");
	tmp = s;
	s = ft_strjoin(s, cmd);
	free(tmp);
	return (s);
}

/*
** waitpid() return -1 on error
** pid > 0 = parent
** pid == 0 = child
*/

int			exec_bin(char *path, char **args, t_list *env_list)
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**env;

	pid = fork();
	env = NULL;
	if (pid > 0)
	{
		ret = waitpid(0, &status, 0);
	}
	else if (pid == 0)
	{
		env = list_to_array(env_list);
		if (!env)
			return (0);
		ret = execve(path, args, env);
		free_split(args);
		free_split(env);
	}
	else
		printf("ERROR - fork\n");
	return (0);
}

static int	search_bin(char **cmd, t_list *env_list)
{
	int	ret_exec;

	ret_exec = 0;
	if (is_builtin(cmd))
		ret_exec = exec_from_builtins(cmd, env_list);
	else if (is_path(cmd[0]))
		ret_exec = exec_from_path(cmd, env_list);
	else
		ret_exec = exec_from_bins(cmd, env_list);
	return (ret_exec);
}

int			exec(char ***cmds, t_list *env_list)
{
	int		i;

	i = 0;
	while (cmds[i])
		search_bin(cmds[i++], env_list);
	free_cmds(cmds);
	return (0);
}
