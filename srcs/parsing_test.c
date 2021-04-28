#include "minishell.h"

void	free_token(void *content)
{
	char	*arg;

	arg = ((t_token*)content)->arg;
	if (arg)
		free(arg);
	free(content);
}

char    *enum_to_str(int state)
{
	if (state == ARG)
		return ("ARG");
	else if (state == REDIR_INF)
		return ("REDIR_INF");
	else if (state == REDIR_SUP)
		return ("REDIR_SUP");
	else if (state == REDIR_DSUP)
		return ("REDIR_DSUP");
	else if (state == FD)
		return ("FILE");
	else if (state == S_COLON)
		return ("S_COLON");
	return ("ERR STATE");
}

size_t		init_args_and_buffer(t_list **args, char **buffer, char **tmp, char *line)
{
	size_t	line_len;

	*args = NULL;
	line_len = ft_strlen(line) + 1;
	*buffer = malloc(sizeof(char) * line_len);
	ft_bzero(*buffer, line_len);
	*tmp = *buffer;
	return (line_len);
}

void	display_args(t_list *args)
{
	int		i;
	t_token	*token;
	size_t	len;

	i = 0;
	printf("i\tstr\t\t\t\tlen\t\ttype\n");
	printf("____________________________________________________________\n");
	while (args)
	{
		token = args->content;
		len = ft_strlen(token->arg);
		printf("%d\t\"%-20.20s\"\t\t%zu\t\t%s\n", i++, token->arg, len, enum_to_str(token->type));
		args = args->next;
	}
	printf("\n");
}

int		add_to_args(t_list **args, char **buffer, char **tmp)
{
	t_token				*token;
	enum types	type;

	//	if (type == REDIR_INF || type == REDIR_SUP || type == REDIR_DSUP)
	//		type = FD;
	//	else
	//		type = ARG;
	type = ARG;
	if (ft_strncmp(*buffer, ";", ft_strlen(*buffer)) == 0)
		type = S_COLON;
	if (**buffer)
	{
		/*
		   if (**buffer == '<')
		   type = REDIR_INF;
		   else if (**buffer == '>')
		   {
		   if (*((*buffer) + 1) == '>')
		   type = REDIR_DSUP;
		   else
		   type = REDIR_SUP;
		   }
		   */
		token = malloc(sizeof(t_token));
		token->type = type;
		token->arg = ft_strdup(*buffer);
		ft_lstadd_back(args, ft_lstnew(token));
		ft_bzero(*buffer, *tmp - *buffer);
		*tmp = *buffer;
	}
	return (1);
}

t_list	*parsing(char *line)
{
	t_list		*args;
	char		*buffer;
	char		*tmp;
	char		*orig_line;
	size_t		line_len;
	enum state	state;

	line_len = init_args_and_buffer(&args, &buffer, &tmp, line);
	state = NORMAL;
	orig_line = line;
	while ((size_t)(line - orig_line) < line_len)
	{
		// B_SLASH
		if (*line == '\\' && state == NORMAL)
		{
			state = B_SLASH;
			line++;
			if (*line)
			{
				if (*line == '$')
					*line = -'$';
				*(tmp++) = *line;
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
				if (*line == '$')
					*line = -(*line);
				*(tmp++) = *(line++);
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
					*(tmp++) = *(line);
				else if (*line == '$')
					*(tmp++) = -'$';
				else 
				{
					*(tmp++) = '\\';
					*(tmp++) = *(line);
				}
			}
			else
				*(tmp++) = *(line);
		}
		else if (*line == '\"' && state == D_QUOTE)
			state = NORMAL;

		// NORMAL
		else if (*line == ';' && state == NORMAL)
		{
			if (*buffer)
				add_to_args(&args, &buffer, &tmp);
			*(tmp++) = ';';
			add_to_args(&args, &buffer, &tmp);
		}
		else if (*line != ' ' && *line != '\0' && state == NORMAL)
			*(tmp++) = *line;
		else if ((*line == ' ' || *line == '\0') && state == NORMAL)
			add_to_args(&args, &buffer, &tmp);
		line++;
	}
	if (state != NORMAL)
	{
		ft_putstr_fd("mini-michel - syntax error\n", STDERR_FILENO);
		ft_lstclear(&args, free_token);
	}
	free(buffer);
	return (args);
}
