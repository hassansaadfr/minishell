#include "minishell.h"

void	dollar_in_d_quote(t_parse *p, char **line)
{
	if (**line == ' ' || **line == '\'')
	{
		*(p->buffer++) = -(**line);
		p->state = D_QUOTE;
	}
	else if (**line == '\"')
	{
		*(p->buffer++) = **line;
		p->state = NORMAL;
	}
	else if (**line == '\\')
	{
		p->state = D_QUOTE;
		*(p->buffer++) = *((*line)++);
		if (**line == '\"' || **line == '\\' || **line == '$')
			*(p->buffer++) = -(**line);
		else
		{
			*(p->buffer - 1) = -'\\';
			*(p->buffer++) = -(**line);
		}
	}
	else
		*(p->buffer++) = **line;
}

void	open_d_quote(t_parse *p, char **line)
{
	*(p->buffer++) = **line;
	p->state = D_QUOTE;
}

void	close_d_quote(t_parse *p, char **line)
{
	*(p->buffer++) = **line;
	p->state = NORMAL;
}
