#include "minishell.h"

int	init_buff_and_history(t_input *buff, t_list **history)
{
	buff->buffer = ft_alloc(INPUT_MAX);
	if (buff->buffer == NULL)
		return (1);
	ft_bzero(buff->buffer, INPUT_MAX);
	buff->backup = ft_alloc(INPUT_MAX);
	if (buff->backup == NULL)
	{
		ft_free_ptr((void **)&buff->buffer);
		return (1);
	}
	ft_bzero(buff->backup, INPUT_MAX);
	buff->pos = NULL;
	buff->i = 0;
	buff->factor = 1;
	*history = NULL;
	g_global.buff = buff;
	return (0);
}

static char	*get_env_term(t_list *env_list)
{
	char	*term_type;
	t_list	*tmp;

	tmp = NULL;
	term_type = NULL;
	tmp = get_env(env_list, "TERM");
	if (tmp)
		term_type = ((t_env *)tmp->content)->value;
	return (term_type);
}

int	init_termcaps(t_list *env_list)
{
	int		ret_tgetent;
	char	*term_type;

	term_type = get_env_term(env_list);
	if (term_type == NULL)
	{
		ft_putstr_fd("ERROR - \"TERM\" not set in env\n", STDERR_FILENO);
		return (0);
	}
	ret_tgetent = tgetent(NULL, term_type);
	if (ret_tgetent == -1)
	{
		ft_putstr_fd("ERROR - Could not access Termcaps DB\n", STDERR_FILENO);
		return (0);
	}
	if (ret_tgetent == 0)
	{
		ft_putstr_fd("ERROR - Termcap type \"", STDERR_FILENO);
		ft_putstr_fd(term_type, STDERR_FILENO);
		ft_putstr_fd("\" is not in Termcap DB\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

size_t	init_parse_struct(t_parse *p, char *line)
{
	size_t	line_len;

	p->tokens = NULL;
	line_len = ft_strlen(line) + 1;
	p->buffer_start = ft_alloc(sizeof(char) * line_len);
	ft_bzero(p->buffer_start, line_len);
	p->buffer = p->buffer_start;
	p->state = NORMAL;
	p->line_start = line;
	return (line_len);
}

void	init_expand_struct(t_expand *exp, t_token *token)
{
	exp->key_len = 0;
	exp->beginning = token->arg;
	exp->remaining = NULL;
	exp->expansion = NULL;
	exp->new_arg = NULL;
	exp->tmp_c = '\0';
	exp->tmp_new_arg = NULL;
	exp->tmp_remaining = NULL;
}
