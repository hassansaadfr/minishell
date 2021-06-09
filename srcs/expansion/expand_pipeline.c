#include "minishell.h"

void	expand_pipeline(t_cmd_and_redir *pipeline, int cmd_count, t_list *env_list)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		pipeline[i].cmd = expand_args(&pipeline[i].cmd, env_list);
		pipeline[i].redirs = expand_args(&pipeline[i].redirs, env_list);
		i++;
	}
}
