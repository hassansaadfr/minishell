#include "minishell.h"

void	backslash(t_parse *p, char **line)
{
	p->state = B_SLASH;
	(*line)++;
	if (**line)
	{
		if (**line == '$' || **line == ';')
			**line = -(**line);
		*(p->buffer++) = **line;
		p->state = NORMAL;
	}
}

void	s_quote(t_parse *p, char **line)
{
	(*line)++;
	p->state = S_QUOTE;
	while (**line && **line != '\'')
	{
		if (**line == '$' || **line == ';')
			**line = -(**line);
		*(p->buffer) = **line;
		p->buffer++;
		(*line)++;
	}
	if (**line == '\'')
		p->state = NORMAL;
}

void	d_quote(t_parse *p, char **line)
{
	if (**line == '\"' && p->state == NORMAL)
		p->state = D_QUOTE;
	else if (**line && p->state == D_QUOTE && **line != '\"')
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line == '\"' || **line == '\\')
				*(p->buffer++) = **line;
			else if (**line == '$')
				*(p->buffer++) = -(**line);
			else
			{
				*(p->buffer++) = '\\';
				*(p->buffer++) = **(line);
			}
		}
		else if (**line == ';')
			*(p->buffer++) = -(**line);
		else
			*(p->buffer++) = **line;
	}
	else if (**line == '\"' && p->state == D_QUOTE)
		p->state = NORMAL;
}

int		metachar_or_space(t_parse *p, char **line)
{
	int		ret_add;

	ret_add = 1;
	if (**line == ';' && p->state == NORMAL)
	{
		if (*(p->buffer_start) != '\0')
			ret_add = add_to_tokens_list(p);
		*(p->buffer++) = ';';
	}
	if (ret_add == 1)
		ret_add = add_to_tokens_list(p);
	return (ret_add);
}

int		is_metachar(char c)
{
	return (c == ';');
}
