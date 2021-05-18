#ifndef STRUCT_H

# define STRUCT_H

# include "libft.h"

typedef struct termios	t_termios;

typedef struct			s_env
{
	char	*name;
	char	*value;
}						t_env;

typedef struct			s_input
{
	char	*buffer;
	char	*backup;
	t_list	*pos;
	int		i;
	int		factor;
}						t_input;

typedef struct			s_global
{
	t_list	*env_list;
	pid_t	pid;
	t_input	*buff;
}						t_global;

t_global				g_global;

enum					e_types
{
	ERR_TYPE,
	ARG,
	FD,
	REDIR_INF,
	REDIR_SUP,
	REDIR_DSUP,
	PIPE,
	S_COLON,
	NEWLINE
};

enum					e_state
{
	NORMAL,
	S_QUOTE,
	D_QUOTE,
	B_SLASH,
	DLR_DQ
};

typedef struct			s_parse
{
	t_list			*tokens;
	char			*buffer_start;
	char			*buffer;
	char			*line_start;
	size_t			line_len;
	enum e_state	state;
}						t_parse;

typedef struct			s_token
{
	int		type;
	char	*arg;
}						t_token;

#endif
