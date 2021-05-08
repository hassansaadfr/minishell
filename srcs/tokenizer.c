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
	char				err_char;

	type = find_token_type(p);
	if (type == ERR_TYPE)
	{
		err_char = *(p->buffer_start);
		ft_bzero(p->buffer_start, p->buffer - p->buffer_start);
		p->buffer = p->buffer_start;
		return (-err_char);
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

int		split_into_tokens(t_parse *p, char **line)
{
	int	ret_mtc_or_spc;

	ret_mtc_or_spc = 1;
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
		else if (**line == ' ' && not_empty(p->buffer_start) && p->state == NORMAL)
		{
			ret_mtc_or_spc = space(p, line);
			if (ret_mtc_or_spc <= 0)
				return (ret_mtc_or_spc);
		}
		else if (is_metachar(**line) && not_empty(p->buffer_start) && p->state == NORMAL)
		{
			ret_mtc_or_spc = metachar(p, line);
			if (ret_mtc_or_spc <= 0)
				return (ret_mtc_or_spc);
		}
		else if (**line != ' ' && **line != '\0' && p->state == NORMAL)
			*(p->buffer++) = **line;
		(*line)++;
	}
	return (1);
}

t_list	*parsing(char *line)
{
	t_parse		p;
	int			ret_tokenizing;

	ret_tokenizing = 1;
	p.line_len = init_parse_struct(&p, line);
	ret_tokenizing = split_into_tokens(&p, &line);
	free(p.buffer_start);
	return (check_parsing_errors(p, ret_tokenizing));
}
