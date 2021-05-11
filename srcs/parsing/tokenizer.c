#include "minishell.h"

void	reset_token_buffer(t_parse *p)
{
	ft_bzero(p->buffer_start, p->buffer - p->buffer_start);
	p->buffer = p->buffer_start;
}

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

	type = typing(p);
	if (type == ERR_TYPE)
		return (-p->buffer_start[0]);
	if (not_empty(p->buffer_start))
	{
		new_node = alloc_token_node(p, type);
		if (new_node == NULL)
			return (0);
		ft_lstadd_back(&p->tokens, new_node);
		reset_token_buffer(p);
	}
	return (1);
}

int		split_into_tokens(t_parse *p, char **line)
{
	int	ret_add;

	ret_add = 1;
	while ((size_t)(*line - p->line_start) < p->line_len)
	{
		if (**line == '\\' && p->state == NORMAL)
			backslash(p, line);
		else if (**line == '\'' && p->state == NORMAL)
			s_quote(p, line);
		else if (d_quote_conditions(p, line))
			d_quote(p, line);
		else if ((**line == ' ' || **line == '\0') && p->state == NORMAL)
			ret_add = space_or_null(p);
		else if (is_metachar(**line) && p->state == NORMAL)
			ret_add = metachar(p, line);
		else if (**line != ' ' && **line != '\0' && p->state == NORMAL)
			*(p->buffer++) = **line;
		if (ret_add <= 0)
			return (ret_add);
		(*line)++;
	}
	if (newline_exclusions(ft_lstlast(p->tokens)) == 0)
		return (-NEWLINE);
	return (1);
}

/*
**	PROTECT p->buffer_start ALLOCATION
**	OR PASS AN ALREADY ALLOCATED BUFFER LARGE ENOUGH
**		=> (t_input buff.backup)
*/

t_list	*parsing(char *line)
{
	t_parse		p;
	int			ret_tokenizing;

	ret_tokenizing = 1;
	p.line_len = init_parse_struct(&p, line);
	if (p.line_len == 0)
		return (check_parsing_errors(&p, 0));
	ret_tokenizing = split_into_tokens(&p, &line);
	return (check_parsing_errors(&p, ret_tokenizing));
}
