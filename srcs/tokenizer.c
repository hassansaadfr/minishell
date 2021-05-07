#include "minishell.h"

t_list	*alloc_token_node(t_parse *p, int type)
{
	t_token				*token;
	t_list				*new_node;

	new_node = NULL;
	if (*(p->buffer_start) != '\0')
	{
		token = malloc(sizeof(t_token));
		if (token == NULL)
			return (NULL);
		token->type = type;
		token->arg = ft_strdup(p->buffer_start);
		if (token->arg == NULL)
		{
			free(token);
			return (NULL);
		}
		new_node = ft_lstnew(token);
		if (new_node == NULL)
		{
			free_token(token);
			return (NULL);
		}
	}
	return (new_node);
}

int		add_to_tokens_list(t_parse *p)
{
	t_list				*new_node;
	enum e_types		type;

	type = find_token_type(p);
	if (type == ERR_TYPE)
	{
		ft_bzero(p->buffer_start, p->buffer - p->buffer_start);
		p->buffer = p->buffer_start;
		return (-1);
	}
	if (*(p->buffer_start) != '\0')
	{
		new_node = alloc_token_node(p, type);
		if (new_node == NULL)
			return (0);
		ft_lstadd_back(&p->tokens, new_node);
		ft_bzero(p->buffer_start, p->buffer - p->buffer_start);
		p->buffer = p->buffer_start;
	}
	return (1);
}

void	split_into_tokens(t_parse *p, char **line, int *ret_mtc_or_spc)
{
	while ((size_t)(*line - p->line_start) < p->line_len)
	{
		if (**line == '\\' && p->state == NORMAL)
			backslash(p, line);
		else if (**line == '\'' && p->state == NORMAL)
			s_quote(p, line);
		else if ((**line == '\"' && p->state == NORMAL)
				|| (**line && p->state == D_QUOTE && **line != '\"')
				|| (**line == '\"' && p->state == D_QUOTE))
			d_quote(p, line);
		else if ((**line == ';' || **line == ' ' || **line == '\0')
				&& p->buffer_start[0] != '\0' && p->state == NORMAL)
		{
			*ret_mtc_or_spc = metachar_or_space(p, line);
			if (*ret_mtc_or_spc <= 0)
				return ;
		}
		else if (**line != ' ' && **line != '\0' && p->state == NORMAL)
			*(p->buffer++) = **line;
		(*line)++;
	}
}

t_list	*check_parsing_errors(t_parse p, int ret_mtc_or_spc)
{
	if (p.state != NORMAL)
	{
		ft_putstr_fd("minishell - QUOTING syntax error\n", STDERR_FILENO);
		ft_lstclear(&p.tokens, free_token);
		return (NULL);
	}
	else if (ret_mtc_or_spc == -1)
	{
		ft_putstr_fd("minishell - TYPE syntax error near unexpected symbol \" \"\n", STDERR_FILENO);
		ft_lstclear(&p.tokens, free_token);
		return (NULL);
	}
	else if (ret_mtc_or_spc == 0)
	{
		ft_putstr_fd("minishell - alloc error\n", STDERR_FILENO);
		return (NULL);
	}
	return (p.tokens);
}

t_list	*parsing(char *line)
{
	t_parse		p;
	int			ret_mtc_or_spc;

	ret_mtc_or_spc = 1;
	p.line_len = init_parse_struct(&p, line);
	split_into_tokens(&p, &line, &ret_mtc_or_spc);
	free(p.buffer_start);
	return (check_parsing_errors(p, ret_mtc_or_spc));
}
