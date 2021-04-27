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
	int		reset_buffer;
	t_buff	*buff;
}						t_global;

t_global				g_global;

enum	types
{
	ARG,
	REDIR
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
