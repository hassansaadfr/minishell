#include "minishell.h"

void	bufferize_redir_dsup(t_parse *p, char **line)
{
	*(p->buffer++) = *((*line)++);
	*(p->buffer++) = **line;
}

int		metachar(t_parse *p, char **line)
{
	int     ret_add;

	ret_add = 1;
	if (not_empty(p->buffer_start))
		ret_add = add_to_tokens_list(p);
	if (ft_strncmp(*line, ">>", 2) == 0)
		bufferize_redir_dsup(p, line);	
	else
		*(p->buffer++) = **line;
	if (ret_add == 1)
		ret_add = add_to_tokens_list(p);
	return (ret_add);
}

int		space_or_null(t_parse *p)
{
	if (not_empty(p->buffer_start))
		return (add_to_tokens_list(p));
	else
		return (1);
}

int		is_metachar(char c)
{
	return (c == ';' || c == '>' || c == '<' || c == '|');
}
