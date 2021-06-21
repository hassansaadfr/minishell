#include "minishell.h"

int	should_concat(char *name)
{
	char	*equal_pos;
	int		out;
	int		len;

	out = 1;
	len = 0;
	if (name == NULL)
		return (out);
	equal_pos = ft_strchr(name, '=');
	if (equal_pos == NULL)
		return (1);
	*equal_pos = '\0';
	len = ft_strlen(name);
	if (name[len - 1] == '+')
		out = 0;
	*equal_pos = '=';
	return (out);
}

char	*parse_env_name_concat(char *env)
{
	char	*name;
	char	*equal_pos;

	name = NULL;
	equal_pos = NULL;
	if (!env)
		return (NULL);
	equal_pos = ft_strchr(env, '+');
	if (equal_pos == NULL)
		name = ft_strdup(env);
	if (equal_pos != NULL)
	{
		*equal_pos = '\0';
		if (ft_strlen(env) > 0)
			name = ft_strdup(env);
		*equal_pos = '+';
	}
	return (name);
}

int	concat_env(char *env_var, t_list *env_list)
{
	t_list	*env_node;
	char	*parsed_name;
	char	*val;

	parsed_name = parse_env_name_concat(env_var);
	if (parsed_name == NULL)
		return (1);
	env_node = get_env(env_list, parsed_name);
	if (env_node != NULL)
	{
		val = ((t_env *)env_node->content)->value;
		if (val == NULL)
			val = "";
		((t_env *)env_node->content)->value = ft_strjoin(val,
				ft_strchr(env_var, '=') + 1);
		ft_free_ptr((void **)&parsed_name);
		ft_free_ptr((void **)&val);
		return (0);
	}
	else if (env_node == NULL)
	{
		new_env(env_list, ft_strjoin(parsed_name, ft_strchr(env_var, '=')));
		return (0);
	}
	return (1);
}
