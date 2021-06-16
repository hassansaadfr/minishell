#include "minishell.h"

int	is_pipeline(t_list *indpdt_cmd)
{
	while (indpdt_cmd)
	{
		if (token_is(PIPE, indpdt_cmd->content))
			return (1);
		indpdt_cmd = indpdt_cmd->next;
	}
	return (0);
}

int	count_pipes(t_list *pipeline)
{
	int	count;

	count = 0;
	while (pipeline)
	{
		if (token_is(PIPE, pipeline->content))
			count++;
		pipeline = pipeline->next;
	}
	return (count);
}

void	init_splitted_pipeline(t_pipeline *pipes_arr, int count)
{
	int	i;

	i = 0;
	while (i < count + 1)
	{
		pipes_arr[i].cmd = NULL;
		pipes_arr[i].redirs = NULL;
		i++;
	}
}

void	assign_in_struct_array(t_list *to_add, t_pipeline *pipes_arr,
		int *i)
{
	to_add->next = NULL;
	to_add->previous = NULL;
	if (token_is(ARG, to_add->content))
		ft_lstadd_back(&pipes_arr[*i].cmd, to_add);
	else if (is_redir_or_fd(to_add))
		ft_lstadd_back(&pipes_arr[*i].redirs, to_add);
	else if (token_is(PIPE, to_add->content))
		(*i)++;
}

void	split_pipeline(t_list *pipeline, t_pipeline *pipes_arr)
{
	t_list	*to_add;
	int		i;

	i = 0;
	while (pipeline)
	{
		to_add = pipeline;
		pipeline = pipeline->next;
		assign_in_struct_array(to_add, pipes_arr, &i); 
	}
}
