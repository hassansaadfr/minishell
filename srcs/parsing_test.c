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

size_t		init_list_and_buffer(t_list **tokens, char **buffer_start, char **buffer, char *line)
{
	size_t	line_len;

	*tokens = NULL;
	line_len = ft_strlen(line) + 1;
	*buffer_start = malloc(sizeof(char) * line_len);
	ft_bzero(*buffer_start, line_len);
	*buffer = *buffer_start;
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
		/*
		   if (**buffer_start == '<')
		   type = REDIR_INF;
		   else if (**buffer_start == '>')
		   {
		   if (*((*buffer_start) + 1) == '>')
		   type = REDIR_DSUP;
		   else
		   type = REDIR_SUP;
		   }
		   */
		token = malloc(sizeof(t_token));
		token->type = type;
		token->arg = ft_strdup(*buffer_start);
		ft_lstadd_back(tokens, ft_lstnew(token));
		ft_bzero(*buffer_start, *buffer - *buffer_start);
		*buffer = *buffer_start;
	}
	return (1);
}

t_list	*parsing(char *line)
{
	t_parsing		p;
	t_list			*tokens;
	char			*buffer_start;
	char			*buffer;
	char			*line_start;
	size_t			line_len;
	enum e_state	state;

	line_len = init_list_and_buffer(&tokens, &buffer_start, &buffer, line);
	state = NORMAL;
	line_start = line;
	while ((size_t)(line - line_start) < line_len)
	{
		// B_SLASH
		if (*line == '\\' && state == NORMAL)
		{
			state = B_SLASH;
			line++;
			if (*line)
			{
				if (*line == '$' || *line == ';')
					*line = -*line;
				*(buffer++) = *line;
				state = NORMAL;
			}
		}

		// S_QUOTE
		else if (*line == '\'' && state == NORMAL)
		{
			line++;
			state = S_QUOTE;
			while (*line && *line != '\'')
			{
				if (*line == '$' || *line == ';')
					*line = -(*line);
				*(buffer++) = *(line++);
			}
			if (*line == '\'')
				state = NORMAL;
		}

		// D_QUOTE
		else if (*line == '\"' && state == NORMAL)
			state = D_QUOTE;
		else if (*line && state == D_QUOTE && *line != '\"')
		{
			if (*line == '\\')
			{
				line++;
				if (*line == '\"' || *line == '\\')
					*(buffer++) = *(line);
				else if (*line == '$')
					*(buffer++) = -*line;
				else 
				{
					*(buffer++) = '\\';
					*(buffer++) = *(line);
				}
			}
			else if (*line == ';')
				*(buffer++) = -*line;
			else
				*(buffer++) = *(line);
		}
		else if (*line == '\"' && state == D_QUOTE)
			state = NORMAL;

		// NORMAL
		else if (*line == ';' && state == NORMAL)
		{
			if (*buffer_start)
				add_to_tokens(&tokens, &buffer_start, &buffer);
			*(buffer++) = ';';
			add_to_tokens(&tokens, &buffer_start, &buffer);
		}
		else if (*line != ' ' && *line != '\0' && state == NORMAL)
			*(buffer++) = *line;
		else if ((*line == ' ' || *line == '\0') && state == NORMAL)
			add_to_tokens(&tokens, &buffer_start, &buffer);
		line++;
	}
	free(buffer_start);

	// SYNTAX ERROR DETECTION
	if (state != NORMAL)
	{
		ft_putstr_fd("mini-michel - syntax error\n", STDERR_FILENO);
		ft_lstclear(&tokens, free_token);
		return (NULL);
	}
	return (tokens);
}
