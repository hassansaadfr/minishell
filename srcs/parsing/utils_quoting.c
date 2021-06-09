#include "minishell.h"

void	backslash(t_parse *p, char **line)
{
	p->state = B_SLASH;
	*(p->buffer++) = *((*line)++);
	if (**line)
	{
		*(p->buffer++) = -(**line);
		p->state = NORMAL;
	}
}

void	s_quote(t_parse *p, char **line)
{
	p->state = S_QUOTE;
	*(p->buffer++) = *((*line)++);
	while (**line && **line != '\'')
	{
		*(p->buffer) = -(**line);
		p->buffer++;
		(*line)++;
	}
	if (**line == '\'')
	{
		p->state = NORMAL;
		*(p->buffer++) = **line;
	}
}

void	d_quote(t_parse *p, char **line)
{
	if (**line == '\"' && p->state == NORMAL)
		open_d_quote(p, line);
	else if (**line && p->state == D_QUOTE && **line != '\"')
	{
		if (**line == '\\')
		{
			*(p->buffer++) = *((*line)++);
			if (**line == '\"' || **line == '\\' || **line == '$')
				*(p->buffer++) = -(**line);
			else
			{
				*(p->buffer - 1) = -'\\';
				*(p->buffer++) = -(**line);
			}
		}
		else if (**line == '$')
		{
			*(p->buffer++) = **line;
			p->state = DLR_DQ;
		}
		else
			*(p->buffer++) = -(**line);
	}
	else if (**line == '\"' && p->state == D_QUOTE)
		close_d_quote(p, line);
}
