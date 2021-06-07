#include "minishell.h"

static char	**parse_cmd(char *splitted)
{
	char	**splitted_cmd;

	splitted_cmd = ft_split(splitted, ' ');
	return (splitted_cmd);
}

/*
** TODO
** Check return of split
*/

char	***parse(char *cmd)
{
	int		i;
	char	**splitted;
	char	***cmd_list;
	int		size;

	i = 0;
	splitted = ft_split(cmd, ';');
	size = get_strarr_size(splitted);
	cmd_list = ft_alloc(sizeof(char *) * (size + 1));
	cmd_list[size] = NULL;
	while (splitted[i])
	{
		cmd_list[i] = parse_cmd(splitted[i]);
		i++;
	}
	free_split(splitted);
	return (cmd_list);
}
