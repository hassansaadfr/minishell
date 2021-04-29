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
