#include "minishell.h"

void	free_token(void *content)
{
	char	*arg;

	arg = ((t_token*)content)->arg;
	if (arg)
		free(arg);
	free(content);
}

char    *enum_to_str(int type)
{
	if (type == ARG)
		return ("ARG");
	else if (type == REDIR_INF)
		return ("REDIR_INF");
	else if (type == REDIR_SUP)
		return ("REDIR_SUP");
	else if (type == REDIR_DSUP)
		return ("REDIR_DSUP");
	else if (type == FD)
		return ("FILE");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == S_COLON)
		return ("S_COLON");
	return ("ERR STATE");
}

size_t		init_parse_struct(t_parse *p, char *line)
{
	size_t	line_len;

	p->tokens = NULL;
	line_len = ft_strlen(line) + 1;
	p->buffer_start = malloc(sizeof(char) * line_len);
	ft_bzero(p->buffer_start, line_len);
	p->buffer = p->buffer_start;
	return (line_len);
}

void	display_tokens(t_list *tokens)
{
	int		i;
	t_token	*token;
	size_t	len;

	i = 0;
	printf("i\tstr\t\t\t\tlen\t\ttype\n");
	printf("____________________________________________________________\n");
	while (tokens)
	{
		token = tokens->content;
		len = ft_strlen(token->arg);
		printf("%d\t\"%-20.20s\"\t\t%zu\t\t%s\n", i++, token->arg, len, enum_to_str(token->type));
		tokens = tokens->next;
	}
	printf("\n");
}

/*
   int		add_to_tokens(t_list **tokens, char **buffer_start, char **buffer)
   {
   t_token				*token;
   enum e_types		type;

//	if (type == REDIR_INF || type == REDIR_SUP || type == REDIR_DSUP)
//		type = FD;
//	else
//		type = ARG;
type = ARG;
if (ft_strncmp(*buffer_start, ";", ft_strlen(*buffer_start)) == 0)
type = S_COLON;
if (**buffer_start)
{
//		   if (**buffer_start == '<')
//		   type = REDIR_INF;
//		   else if (**buffer_start == '>')
//		   {
//		   if (*((*buffer_start) + 1) == '>')
//		   type = REDIR_DSUP;
//		   else
//		   type = REDIR_SUP;
//		   }
token = malloc(sizeof(t_token));
token->type = type;
token->arg = ft_strdup(*buffer_start);
ft_lstadd_back(tokens, ft_lstnew(token));
ft_bzero(*buffer_start, *buffer - *buffer_start);
 *buffer = *buffer_start;
 }
 return (1);
 }
 */

t_list	*alloc_token_node(t_parse *p, int type)
{
	t_token				*token;
	t_list				*new_node;

	new_node = NULL;
	if (*(p->buffer_start))
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

	type = ARG;
	if (ft_strncmp(p->buffer_start, ";", ft_strlen(p->buffer_start)) == 0)
		type = S_COLON;
	new_node = alloc_token_node(p, type);
	if (new_node == NULL)
		return (0);
	ft_lstadd_back(&p->tokens, new_node);
	ft_bzero(p->buffer_start, p->buffer - p->buffer_start);
	p->buffer = p->buffer_start;
	return (1);
}

t_list	*parsing(char *line)
{
	t_parse			p;

	p.line_len = init_parse_struct(&p, line);
	p.state = NORMAL;
	p.line_start = line;
	while ((size_t)(line - p.line_start) < p.line_len)
	{
		// B_SLASH
		if (*line == '\\' && p.state == NORMAL)
		{
			p.state = B_SLASH;
			line++;
			if (*line)
			{
				if (*line == '$' || *line == ';')
					*line = -*line;
				*(p.buffer++) = *line;
				p.state = NORMAL;
			}
		}

		// S_QUOTE
		else if (*line == '\'' && p.state == NORMAL)
		{
			line++;
			p.state = S_QUOTE;
			while (*line && *line != '\'')
			{
				if (*line == '$' || *line == ';')
					*line = -(*line);
				*(p.buffer++) = *(line++);
			}
			if (*line == '\'')
				p.state = NORMAL;
		}

		// D_QUOTE
		else if (*line == '\"' && p.state == NORMAL)
			p.state = D_QUOTE;
		else if (*line && p.state == D_QUOTE && *line != '\"')
		{
			if (*line == '\\')
			{
				line++;
				if (*line == '\"' || *line == '\\')
					*(p.buffer++) = *(line);
				else if (*line == '$')
					*(p.buffer++) = -*line;
				else 
				{
					*(p.buffer++) = '\\';
					*(p.buffer++) = *(line);
				}
			}
			else if (*line == ';')
				*(p.buffer++) = -*line;
			else
				*(p.buffer++) = *(line);
		}
		else if (*line == '\"' && p.state == D_QUOTE)
			p.state = NORMAL;

		// NORMAL
		else if (*line == ';' && p.state == NORMAL)
		{
			if (*p.buffer_start)
				add_to_tokens_list(&p);
			*(p.buffer++) = ';';
			add_to_tokens_list(&p);
		}
		else if (*line != ' ' && *line != '\0' && p.state == NORMAL)
			*(p.buffer++) = *line;
		else if ((*line == ' ' || *line == '\0') && p.state == NORMAL)
			add_to_tokens_list(&p);
		line++;
	}
	free(p.buffer_start);

	// SYNTAX ERROR DETECTION
	if (p.state != NORMAL)
	{
		ft_putstr_fd("mini-michel - syntax error\n", STDERR_FILENO);
		ft_lstclear(&p.tokens, free_token);
		return (NULL);
	}
	return (p.tokens);
}
