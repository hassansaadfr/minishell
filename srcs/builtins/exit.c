#include "minishell.h"

static int	code_is_valid(char *arg)
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (2);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (2);
		i++;
	}
	return (0);
}

static char	*get_err_msg(t_list *env_list, int msg)
{
	t_list	*tmp;
	char	*lang;

	lang = NULL;
	tmp = get_env(env_list, "LANG");
	if (tmp && tmp->content)
	{
		lang = ((t_env *)(tmp->content))->value;
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

static int	get_exit_code(char *str, t_list *env_list)
{
	long int		code;
	int				overflow;

	overflow = 0;
	code = ft_atoll(str, &overflow);
	if (overflow)
	{
		print_err("exit", str, get_err_msg(env_list, ARG_NUMERIC));
		return (2);
	}
	return (code % 256);
}

int	builtin_exit(char **argv, t_list *env_list)
{
	int		arr_len;

	argv++;
	arr_len = get_strarr_size(argv);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!*argv)
		ft_exit_free(g_global.last_return);
	if (code_is_valid(*argv) == 2)
	{
		print_err("exit", *argv, get_err_msg(env_list, ARG_NUMERIC));
		ft_exit_free(2);
	}
	else if (arr_len > 1)
	{
		print_err("exit", NULL, get_err_msg(env_list, TOO_MUCH_ARGS));
		if (!isatty(STDIN_FILENO))
			ft_exit_free(1);
	}
	else
		ft_exit_free(get_exit_code(*argv, env_list));
	return (1);
}
