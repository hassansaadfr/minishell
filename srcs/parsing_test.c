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
	else if (state == REDIR)
		return ("REDIR");
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

	i = 0;
	while (args)
	{
		token = args->content;
		printf("%d\t\"%20.20s\"\t\t%s\n", i++, token->arg, enum_to_str(token->type));
		args = args->next;
	}
	printf("\n");
}

int		add_to_args(t_list **args, char **buffer, char **tmp, int state)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = state;
	token->arg = ft_strdup(*buffer);
	ft_lstadd_back(args, ft_lstnew(token));
	ft_bzero(*buffer, *tmp - *buffer);
	*tmp = *buffer;
	return (1);
}

t_list	*parsing(char *line)
{
	t_list		*args;
	char		*buffer;
	char		*tmp;
	char		*orig_line;
	size_t		line_len;
	enum types	type;
	enum state	state;

	line_len = init_args_and_buffer(&args, &buffer, &tmp, line);
	type = ARG;
	state = NORMAL;
	orig_line = line;
	while ((size_t)(line - orig_line) < line_len)
	{
		if (*line == '\\' && state == NORMAL)
		{
			state = B_SLASH;
			line++;
			if (*line)
			{
				*(tmp++) = *line;
				state = NORMAL;
			}
		}
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
		else if (*line != ' ' && *line != '\0' && state == NORMAL)
			*(tmp++) = *line;
		else if ((*line == ' ' || *line == '\0') && state == NORMAL)
			add_to_args(&args, &buffer, &tmp, type);
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
