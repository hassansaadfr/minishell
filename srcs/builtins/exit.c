#include "minishell.h"

static int	is_numeric(char *arg)
{
	int		i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*get_err_msg(t_list *env_list, int msg)
{
	t_list	*tmp;
	char	*lang;
	lang = NULL;
	tmp = get_env(env_list, "LANG");
	if (tmp && tmp->content)
	{
		lang = ((t_env*)(tmp->content))->value;
		if (lang)
		{
			if (ft_strncmp("fr_FR", lang, 5) == 0)
			{
				if (msg == ARG_NUMERIC)
					return (ft_strdup(ARG_NUMERIC_FR));
				else
					return (ft_strdup(TOO_MUCH_ARGS_FR));
			}
		}
	}
	if (msg == ARG_NUMERIC)
		return (ft_strdup(ARG_NUMERIC_EN));
	else
		return (ft_strdup(TOO_MUCH_ARGS_EN));
}

static int	get_exit_code(char *str)
{
	int		code;

	code = ft_atoi(str);
	if (code < 0)
	{
		while (code < 0 && code < 256)
			code = code + 256;
	}
	else
	{
		while (code > 256)
			code -= 256;
	}
	return (code);
}

int			builtin_exit(char **argv, t_list *env_list)
{
	int		arr_len;
	char	*msg;

	msg = NULL;
	argv++;
	arr_len = get_strarr_size(argv);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (arr_len > 1)
	{
		ft_putendl_fd(ft_strjoin("minishell: line 1: exit: ", get_err_msg(env_list, TOO_MUCH_ARGS)), STDERR_FILENO);
		if (!isatty(STDIN_FILENO))
			ft_exit_free(1);
	}
	else
	{
		if (!*argv)
			ft_exit_free(0);
		if (is_numeric(*argv))
			ft_exit_free(get_exit_code(*argv));
		else
		{
			ft_putstr_fd(ft_strjoin("minishell: exit ", get_err_msg(env_list, ARG_NUMERIC)), STDERR_FILENO);
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putstr_fd(" : ", STDERR_FILENO);
			ft_putendl_fd(msg, STDERR_FILENO);
			ft_free_ptr((void**)&msg);
			ft_exit_free(2);
		}
	}
	return (1);
}
