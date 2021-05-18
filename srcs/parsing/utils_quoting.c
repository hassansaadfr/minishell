#include "minishell.h"

void	backslash(t_parse *p, char **line)
{
	p->state = B_SLASH;
	(*line)++;
	if (**line)
	{
		//	if (is_metachar(**line) || **line == '$')
		//		**line = -(**line);
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
		//		if (is_metachar(**line) || **line == '$')
		//			**line = -(**line);
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
		p->state = D_QUOTE;
	else if (**line == '\"')
	{	
		*(p->buffer++) = **line;
		p->state = NORMAL;
	}
	else
		*(p->buffer++) = **line;
}

int         d_quote_conditions(t_parse *p, char **line)
{
	return ((**line == '\"' && p->state == NORMAL)
			|| (**line && p->state == D_QUOTE && **line != '\"')
			|| (**line == '\"' && p->state == D_QUOTE));
}

void	d_quote(t_parse *p, char **line)
{
	if (**line == '\"' && p->state == NORMAL)
	{
		*(p->buffer++) = **line;
		p->state = D_QUOTE;
	}
	else if (**line && p->state == D_QUOTE && **line != '\"')
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line == '\"' || **line == '\\' || **line == '$')
				*(p->buffer++) = -(**line);
			//		else if (**line == '$')
			//			*(p->buffer++) = -(**line);
			else
			{
				*(p->buffer++) = -'\\';
				*(p->buffer++) = -(**line);
			}
		}
		//		else if (is_metachar(**line))
		//			*(p->buffer++) = -(**line);
		else if (**line == '$')
		{
			*(p->buffer++) = **line;
			p->state = DLR_DQ;
		}
		else
			*(p->buffer++) = -(**line);
	}
	else if (**line == '\"' && p->state == D_QUOTE)
	{
		*(p->buffer++) = **line;
		p->state = NORMAL;
	}
}
