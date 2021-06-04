#include "minishell.h"

static char	**token_list_to_array(t_list *token_list)
{
	int		size;
	char	**array;
	int		i;
	t_list	*tmp_lst;

	size = ft_lstsize(token_list);
	i = 0;
	array = ft_alloc(sizeof(char *) * (size + 1));
	array[size] = NULL;
	tmp_lst = token_list;
	while (tmp_lst)
	{
		array[i] = ft_strdup(((t_token *)(tmp_lst->content))->arg);
		i++;
		tmp_lst = tmp_lst->next;
	}
	return (array);
}

void	init_redirs(t_list *redirs, t_redir_status	*backup)
{
	backup->fd_stdin = -1;
	backup->fd_stdout = -1;
	backup->status = 0;
	if (redirs)
	{
		backup->fd_stdin = dup(STDIN_FILENO);
		backup->fd_stdout = dup(STDOUT_FILENO);
		backup->status = perform_redirections(redirs);
	}
}

static void	restore_fd(t_redir_status *backup)
{
	if (backup->fd_stdin != -1 && backup->fd_stdout != -1)
	{
		dup2(backup->fd_stdin, STDIN_FILENO);
		dup2(backup->fd_stdout, STDOUT_FILENO);
	}
}

int perform_execution(t_list *redirs, t_list *tokens, t_list *env_list)
{
	int				ret_exec;
	char			**cmds;
	t_redir_status	backup;

	ret_exec = 0;
	cmds = NULL;
	if (redirs)
		init_redirs(redirs, &backup);
	if  (tokens && backup.status == 0)
	{
		cmds = token_list_to_array(tokens);
		if (cmds)
		{
			ret_exec = execution(cmds, env_list, NULL);
			free_split(cmds);
		}
		ft_lstclear(&tokens, free_token);
	}
	if (redirs)
	{
		restore_fd(&backup);
	}
	ft_lstclear(&redirs, free_token);
	return (ret_exec);
}
