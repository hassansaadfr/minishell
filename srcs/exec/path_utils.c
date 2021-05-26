#include "minishell.h"

t_path		get_path_type(char *str)
{
	t_path	type;

	type = NO_PATH;
	if (str[0] == '/')
		return (ABSOLUTE_PATH);
	else
	{
		if (ft_strchr(str, '/'))
			return (RELATIVE_PATH);
	}
	return (type);
}
