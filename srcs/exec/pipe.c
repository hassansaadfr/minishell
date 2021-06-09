#include "minishell.h"

int execute_pipeline(t_list *pipeline, t_list *env_list)
{
    (void)env_list;
    int             cmd_count;
    t_cmd_and_redir *splitted_pipeline;

    cmd_count = count_pipes(pipeline) + 1;
    splitted_pipeline = ft_alloc(sizeof(t_cmd_and_redir) * (cmd_count + 1));
    init_splitted_pipeline(splitted_pipeline, cmd_count);
    /*DBG*/printf("cmd_count = %d\n", cmd_count);
    /*DBG*/display_tokens(pipeline);
    split_pipeline(pipeline, splitted_pipeline);
    /*DBG*/display_splitted_pipeline(splitted_pipeline, cmd_count);
    ft_free_ptr((void **)&splitted_pipeline);
    return (0);
}
