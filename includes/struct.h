#ifndef STRUCT_H

# define STRUCT_H

# include "libft.h"

typedef struct s_env
{
	char	*name;
	char	*value;
}						t_env;

typedef struct s_input
{
	char	*buffer;
	char	*backup;
	t_list	*pos;
	int		i;
	int		factor;
}						t_input;

typedef struct s_global
{
	t_list	*env_list;
	pid_t	pid;
	t_input	*buff;
	int		last_return;
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

typedef struct s_parse
{
	t_list			*tokens;
	char			*buffer_start;
	char			*buffer;
	char			*line_start;
	size_t			line_len;
	enum e_state	state;
}						t_parse;

typedef struct s_token
{
	int		type;
	char	*arg;
}						t_token;

typedef struct s_expand
{
	int		key_len;
	char	*beginning;
	char	*expansion;
	char	*remaining;
	char	*new_arg;
	char	tmp_c;
	char	*tmp_new_arg;
	char	*tmp_remaining;
}						t_expand;

typedef struct s_redir_status
{
	int		fd_stdin;
	int		fd_stdout;
	int		status;
}						t_redir_status;

enum					e_err_msg_exit
{
	ARG_NUMERIC,
	TOO_MUCH_ARGS
};

enum					e_path
{
	NO_PATH,
	ABSOLUTE_PATH,
	RELATIVE_PATH
};

typedef enum e_path		t_path;

enum					e_pid
{
	PARENT_PID,
	CHILD_PID,
	ERROR_FORK
};

typedef struct s_msh
{
	int				stop;
	t_list			*history;
	t_input			buff;
	struct termios	orig_termios;
	t_list			*tokens;
}						t_msh;

#endif
