#include "minishell.h"

static int	set_shlvl_value(char *value_env)
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
	{
		if (!ft_isdigit(tmp[j]))
			return (1);
		j++;
	}
	value = ft_atoi(tmp);
	if (value == 999)
	{
		ft_putendl_fd(SHLVL_TOO_HIGH, STDERR_FILENO);
		return (1);
	}
	if (value < 0)
		return (0);
	return (value + 1);
}

char		*init_shlvl(t_list *env_list)
{
	t_list	*tmp;
	t_env	*var;
	int		new_val;

	new_val = 0;
	tmp = get_env(env_list, "SHLVL");
	if (!tmp)
		return (ft_strdup("SHLVL=1"));
	else
	{
		var = tmp->content;
		new_val = set_shlvl_value(var->value);
		return (ft_itoa(new_val));
	}
}

char		*init_path(t_list *env_list)
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
			ft_free_ptr((void**)&buffer);
			return (ft_strjoin("PATH=", tmp));
		}
		close(fd);
		return (NULL);
	}
	return (NULL);
}

char		**create_envp(char *shlvl, char *path)
{
	char	**arr;
	int		size;

	arr = NULL;
	size = 2;
	if (path)
		size++;
	arr = ft_alloc(sizeof(char*) * size);
	arr[0] = shlvl;
	if (path)
	{
		arr[1] = path;
		arr[2] = 0;
	}
	else
		arr[1] = 0;
	return (arr);
}

void		init_path_and_shlvl(t_list **env_list)
{
	char	*shlvl;
	char	*path;
	char	**arr;

	shlvl = init_shlvl(*env_list);
	path = init_path(*env_list);
	if (*env_list == NULL)
	{
		arr = create_envp(shlvl, path);
		*env_list = init_env(arr);
		free_split(arr);
		return ;
	}
	else
	{
		new_env(*env_list, shlvl);
		ft_free_ptr((void**)&shlvl);
		if (path)
		{
			new_env(*env_list, path);
			ft_free_ptr((void**)&path);
		}
		ft_free_ptr((void**)&shlvl);
	}
}
