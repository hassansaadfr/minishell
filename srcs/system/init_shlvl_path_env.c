#include "minishell.h"

static int	get_shlvl_value(char *value_env)
{
	int		i;
	int		j;
	int		value;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(value_env, " ");
	while (tmp[i] && (tmp[i] == '+' || tmp[i] == '-'))
		i++;
	j = i;
	while (tmp[j])
		if (!ft_isdigit(tmp[j++]))
			return (1);
	value = ft_atoi(tmp);
	if (value == 999)
	{
		ft_putstr_fd("minishell: avertissement : ", STDERR_FILENO);
		ft_putstr_fd("niveau de shell trop élevé (1000), ", STDERR_FILENO);
		ft_putstr_fd("initialisation à 1\n", STDERR_FILENO);
		return (1);
	}
	if (value < 0)
		return (0);
	return (value + 1);
}

t_list	*init_shlvl(t_list *env_list)
{
	char	*env_val;
	char	*tmp;
	char	*converted_shlvl;

	tmp = NULL;
	converted_shlvl = NULL;
	env_val = NULL;
	env_val = get_env_value(env_list, "SHLVL");
	if (env_val == NULL)
		return (init_env_node(ft_strdup("SHLVL=1")));
	else
	{
		converted_shlvl = ft_itoa(get_shlvl_value(env_val));
		tmp = ft_strjoin("SHLVL=", converted_shlvl);
		edit_env(env_list, tmp);
		ft_free_ptr((void **)&tmp);
		ft_free_ptr((void **)&converted_shlvl);
		return (NULL);
	}
	return (NULL);
}

char	*init_path(t_list *env_list)
{
	t_list	*tmp_lst;
	char	*tmp;
	char	*buffer;
	int		fd;

	buffer = NULL;
	tmp = NULL;
	tmp_lst = get_env(env_list, "PATH");
	if (!tmp_lst)
	{
		fd = open("/etc/environment", O_RDONLY);
		if (fd < 0)
			return (NULL);
		if (get_next_line(fd, &buffer) > -1)
		{
			close(fd);
			tmp = ft_substr(ft_strchr(buffer, '"'), 1,
					ft_strlen(ft_strchr(buffer, '"')) - 2);
			ft_free_ptr((void **)&buffer);
			return (ft_strjoin("PATH=", tmp));
		}
		close(fd);
		return (NULL);
	}
	return (NULL);
}

void	init_path_and_shlvl(t_list **env_list)
{
	t_list	*sh_lvl;
	char	*path;

	sh_lvl = init_shlvl(*env_list);
	if (sh_lvl)
		ft_lstadd_back(env_list, sh_lvl);
	path = init_path(*env_list);
	if (path)
		ft_lstadd_back(env_list, init_env_node(init_path(*env_list)));
}
