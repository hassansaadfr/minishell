#include "minishell.h"

// PASS tmp_c (FROM expand_in_token()) and 
char    *concat_expansion(char *new_arg, char *key_pos, t_list *env_list)
{
	char    *tmp;
	char    *expansion;

	// IF '$' WAS NOT FOLLOWED BY AN alnum OR A '_', key_pos WILL ALWAYS BE '\0'
	// PASS MORE PARAMS
	if (*key_pos == '\0' || *key_pos == ' ' || *key_pos == -' '
			|| *key_pos == '\\' || *key_pos == -'\\')
		expansion = ft_strdup("$");
	else
		expansion = dup_expansion_value(key_pos, env_list);
	if (expansion != NULL)
	{
		quoting_to_neg(&expansion);
		tmp = new_arg;
		new_arg = ft_strjoin(new_arg, expansion);
		ft_free_ptr((void**)&tmp);
		ft_free_ptr((void**)&expansion);
	}   
	return (new_arg);
}

char    *concat_remaining(char *new_arg, char *remaining)
{
	char    *tmp;

	tmp = new_arg;
	new_arg = ft_strjoin(new_arg, remaining);
	ft_free_ptr((void**)&tmp);
	return (new_arg);
}

void    prepare_concat(char **dollar_pos, char **new_arg, char **remaining,
		char *tmp_c)
{
	char    *tmp;

	**dollar_pos = '\0';
	if (*remaining != *dollar_pos)
	{
		tmp = *new_arg;
		*new_arg = ft_strjoin(*new_arg, *remaining);
		ft_free_ptr((void**)&tmp);
	}
	(*dollar_pos)++;
	*remaining = *dollar_pos;
	while (**remaining && (ft_isalnum(**remaining) || **remaining == '_'))
		(*remaining)++;
	*tmp_c = **remaining;
	**remaining = '\0';
}

char    *dup_expansion_value(char *key_pos, t_list *env_list)
{
	char    *env_value;

	env_value = NULL;
	env_value = get_env_value(env_list, key_pos);
	if (env_value)
		env_value = ft_strdup(env_value);
	return (env_value);
}

void	quoting_to_neg(char **expansion)
{
	int     i;

	i = 0;
	while ((*expansion)[i])
	{
		if (/*(*expansion)[i] == ' ' || */(*expansion)[i] == '\'' 
				|| (*expansion)[i] == '\"' || (*expansion)[i] == '\\')
			(*expansion)[i] = -(*expansion)[i];
		i++;
	}
}
