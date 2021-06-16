#include "minishell.h"

void	display_token_to_be_splitted(t_token *token, char **arg_split)
{
	int	i;

	printf("========================== SPL  0 ==========================\n");
	printf("TOKEN : \"%40s\"\n", token->arg);
	printf("MUST BE SPLITTED AS :\n");
	i = 0;
	while (arg_split[i])
	{
		printf("\t%2d\t\"", i);
		print_token_str(arg_split[i]);
		printf("\"\n");
		i++;
	}
	printf("\n");
}

void	display_splitted_pipeline(t_pipeline *splitted_pipeline, int cmd_count)
{
	int		debug_i;

	debug_i = 0;
	while (debug_i < cmd_count)
	{
		if (splitted_pipeline[debug_i].cmd)
			display_splitted_cmd(splitted_pipeline[debug_i].cmd, debug_i,
				"CMD");
		if (splitted_pipeline[debug_i].redirs)
			display_splitted_cmd(splitted_pipeline[debug_i].redirs, debug_i,
				"RDR");
		debug_i++;
	}
}
