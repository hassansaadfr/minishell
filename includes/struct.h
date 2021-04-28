#ifndef STRUCT_H

# define STRUCT_H

# include "libft.h"

typedef struct termios	t_termios;

typedef struct			s_env
{
	char	*name;
	char	*value;
}						t_env;

typedef struct			s_buff
{
	char	*buffer;
	char	*backup;
	t_list	*pos;
	int		i;
	int		factor;
}						t_buff;

typedef struct			s_global
{
	t_list	*env_list;
	pid_t	pid;
	t_buff	*buff;
}						t_global;

t_global				g_global;

typedef struct			s_parse
{
	t_list	*args;
	char	*buffer;
	char	*tmp;
	char	*line_start;
}						t_parse;

enum	types
{
	ARG,
	REDIR_INF,
	REDIR_SUP,
	REDIR_DSUP,
	FD,
	PIPE,
	S_COLON
};

enum	state
{
	NORMAL,
	S_QUOTE,
	D_QUOTE,
	B_SLASH
};

typedef struct	s_token
{
	int		type;
	char	*arg;
}				t_token;

#endif