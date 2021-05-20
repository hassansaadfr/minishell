#include "minishell.h"

static int	is_numeric(char *arg)
{
	int		i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	if (arg[i] == '-')
		return (1);
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

static void	print_err(char *arg, char *err)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	if (!isatty(STDIN_FILENO))
		ft_putstr_fd(" line 1:", STDERR_FILENO);
	ft_putstr_fd(" exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err, STDERR_FILENO);
}

int			builtin_exit(char **argv, t_list *env_list)
{
	int		arr_len;

	argv++;
	arr_len = get_strarr_size(argv);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!*argv)
		ft_exit_free(0);
	if (!is_numeric(*argv))
	{
		print_err(*argv, get_err_msg(env_list, ARG_NUMERIC));
		ft_exit_free(2);
	}
	else if (arr_len > 1)
	{
		print_err(NULL, get_err_msg(env_list, TOO_MUCH_ARGS));
		if (!isatty(STDIN_FILENO))
			ft_exit_free(1);
	}
	else
		ft_exit_free(get_exit_code(*argv));
	return (1);
}
