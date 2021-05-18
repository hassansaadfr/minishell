#include "minishell.h"

void	backslash(t_parse *p, char **line)
{
	p->state = B_SLASH;
	(*line)++;
	if (**line)
	{
		*(p->buffer++) = -(**line);
		p->state = NORMAL;
	}
}

void	s_quote(t_parse *p, char **line)
{
	(*line)++;
	p->state = S_QUOTE;
	while (**line && **line != '\'')
	{
		*(p->buffer) = -(**line);
		p->buffer++;
		(*line)++;
	}
	if (**line == '\'')
		p->state = NORMAL;
}

void	dollar_in_d_quote(t_parse *p, char **line)
{
	if (**line == ' ')
	{
		*(p->buffer++) = **line;
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
		(*line)++;
		if (**line == '\"' || **line == '\\' || **line == '$')
			*(p->buffer++) = -(**line);
		else
		{
			*(p->buffer++) = -'\\';
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

void	d_quote(t_parse *p, char **line)
{
	if (**line == '\"' && p->state == NORMAL)
		open_d_quote(p, line);
	else if (**line && p->state == D_QUOTE && **line != '\"')
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line == '\"' || **line == '\\' || **line == '$')
				*(p->buffer++) = -(**line);
			else
			{
				*(p->buffer++) = -'\\';
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
