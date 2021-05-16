#include "minishell.h"

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
	ft_free_ptr((void**)&tmp);
	return (s);
}

/*
** waitpid() return -1 on error
** pid > 0 = parent
** pid == 0 = child
*/

int			exec_bin(char *path, char **args, t_list *env_list,
			t_termios orig_termios)
{
	int		ret;
	int		status;
	char	**env;

	disable_raw_mode(orig_termios);
	errno = 0;
	g_global.pid = fork();
	env = NULL;
	if (g_global.pid > 0)
	{
		ret = waitpid(0, &status, 0);
		enable_raw_mode();
		g_global.pid = 0;
	}
	else if (g_global.pid == 0)
	{
		env = list_to_array(env_list);
		ret = execve(path, args, env);
	}
	else
		printf("ERROR - fork\n");
	return (0);
}

static int	search_bin(char **cmd, t_list *env_list, t_termios orig_termios,
		t_list *history)
{
	int	ret_exec;

	ret_exec = 0;
	if (is_builtin(cmd))
		ret_exec = exec_from_builtins(cmd, env_list, history);
	else if (is_path(cmd[0]))
		ret_exec = exec_from_path(cmd, env_list, orig_termios);
	else
		ret_exec = exec_from_bins(cmd, env_list, orig_termios);
	return (ret_exec);
}

int			exec(char ***cmds, t_list *env_list, t_termios orig_termios,
		t_list *history)
{
	int		i;

	i = 0;
	while (cmds[i])
		search_bin(cmds[i++], env_list, orig_termios, history);
	free_cmds(cmds);
	return (0);
}
