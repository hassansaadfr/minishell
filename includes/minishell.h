#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <limits.h>
# include <term.h>
# include <termios.h>
# include <curses.h>  

# include "libft.h"

/*
** 	STRUCTURES AND TYPEDEFS
*/
typedef struct termios	t_termios;

typedef struct			s_global
{
	t_list	*env_list;
//	t_list	*history;
	pid_t	pid;
	int		reset_buffer;
//	int		last_return;
//	t_termios	orig_termios;
}						t_global;

t_global	global;

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

/*
**	DEFINES
*/
# define INPUT_MAX 1024
# define ENTER '\n'
# define DELETE 127
# define ESCAPE 27

# define UP_ARROW 12938712
# define DN_ARROW 1290837


/*
**	FILE - main.c
*/
int			minishell(t_termios orig_termios);

/*
** FILE - parse.c
*/
char		***parse(char *cmd);

/*
** FILE - exec.c
*/
int			exec(char ***cmds, t_list *env_list, t_termios orig_termios);
int			exec_bin(char *path, char **args, t_list *env_list, t_termios orig_termios);
char		*create_full_path(char *bin_path, char *cmd);

/*
** FILE - utils.c
*/
int			get_strarr_size(char **arr);
int			handle_errno(int err, char *binary, char *arg);

/*
**	FILE - debug.c
*/
void		dbg_display_stat_buff(struct stat stat_buff);

/*
**	FILE - prompt.c
*/
//void		prompt(t_list *env_list, t_buff *buff);
void		prompt(t_list *env_list, t_buff *buff);

/*
**	BUILTINS
*/
int			env(t_list *env_list);
int			unset(char *argv, t_list *env_list);
int			builtin_echo(char **argv, t_list *env_list);
int			builtin_cd(char **argv, t_list *env_list);
int			builtin_env(char **argv, t_list *env_list);
int			builtin_exit(char **argv, t_list *env_list);
int			builtin_export(char **argv, t_list *env_list);
int			builtin_pwd(char **argv, t_list *env_list);
int			builtin_unset(char **argv, t_list *env_list);

/*
**	FILE - utils_mem.c
*/
void		free_split(char **splitted);
void		free_cmds(char ***cmds);
void		free_env(t_list **env_list);
void		*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);

/*
**	FILE - utils_env.c
*/
t_list		*init_env(char **envp);
t_list		*get_env(t_list *env_list, char *name);
int			edit_env(t_list *env_list, char *env);
int			delete_env(t_list *env_list, char *name);
int			new_env(t_list *env_list, char *new_env);
t_list		*init_env_node(char *env);
char		*parse_env_value(char *env);
char		*parse_env_name(char *env);
char		**list_to_array(t_list *env_list);

/*
**	FILE - bin_builtins.c
*/
int			is_builtin(char **cmd);
int			exec_from_builtins(char **cmd, t_list *env_list);

/*
**	FILE - bin_paths.c
*/
int			is_path(char *cmd);
int			exec_from_path(char **cmd, t_list *env_list, t_termios orig_termios);

/*
**	FILE - bin_bins.c
*/
int			exec_from_bins(char **cmd, t_list *env_list, t_termios orig_termios);

/*
**	FILE - signals.c
*/
void		signal_handler(int signal_value);


/*
**	FILE - termios.c
*/
t_termios	enable_raw_mode(void);
void		disable_raw_mode(t_termios orig_termios);

/*
**	FILE - initializations.c
*/
int			init_buff_and_history(t_buff *buff, t_list **history);
int			init_termcaps(void);

/*
**	FILE - utils_input.c
*/
int		is_ctrl_keys(char c, int *stop, t_buff *buff, t_list *history);
int		arrow_value(void);
char	ctrl_value(char c);

/*
**	FILE - termcaps.c
*/
int		put_termcap(int c);
void	exec_termcap(char *termcap_name);
void	delete_char(t_buff *buff);
void	clear_line(t_buff *buff);


/*
**	FILE - buffer.c
*/
char	read_key(void);
int		process_key(t_buff *buff);
int     expand_buffers(t_buff *buff);
int     write_buffer(int *stop, t_buff *buff, t_list *history);

/*
**	FILE - history.c
*/
void    display_history(t_list *hist);
int     add_to_history(t_buff *buff, t_list **history);
void    exec_up_arrow(t_buff *buff, t_list *history);
void    exec_down_arrow(t_buff *buff);
void    change_input_str(int arrow, t_buff *buff, t_list *history);

#endif
