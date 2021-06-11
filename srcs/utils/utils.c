#include "minishell.h"

int	get_strarr_size(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}
