#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <limits.h>

# include "libft.h"

/*
**	FILE - main.c
*/
int		minishell(void);

/*
** FILE - parse.c
*/
char	***parse(char *cmd);

/*
** FILE - exec.c
*/
int		exec(char ***cmds, t_list *env_list);
int		exec_bin(char *path, char **args, t_list *env_list);
char	*create_full_path(char *bin_path, char *cmd);

/*
** FILE - utils.c
*/
int		get_strarr_size(char **arr);
int		handle_errno(int err, char *binary, char *arg);

/*
**	FILE - debug.c
*/
void	dbg_display_stat_buff(struct stat stat_buff);

/*
**	FILE - prompt.c
*/
void	prompt(t_list *env_list);

/*
**	Builtins
*/
int		env(t_list *env_list);
int		unset(char *argv, t_list *env_list);
int		builtin_echo(char **argv, t_list *env_list);
int		builtin_cd(char **argv, t_list *env_list);
int		builtin_env(char **argv, t_list *env_list);
int		builtin_exit(char **argv, t_list *env_list);
int		builtin_export(char **argv, t_list *env_list);
int		builtin_pwd(char **argv, t_list *env_list);
int		builtin_unset(char **argv, t_list *env_list);

/*
**	FILE - utils_mem.c
*/
void	free_split(char **tab);
void	free_cmds(char ***cmds);
void	free_env(t_list **env_list);

/*
**	FILE - utils_env.c
*/
t_list	*init_env(char **envp);
t_list	*get_env(t_list *env_list, char *name);
int		edit_env(t_list *env_list, char *env);
int		delete_env(t_list *env_list, char *name);
int		new_env(t_list *env_list, char *new_env);
t_list	*init_env_node(char *env);
char	*parse_env_value(char *env);
char	*parse_env_name(char *env);

/*
**	FILE - bin_builtins.c
*/
int		is_builtin(char **cmd);
int		exec_from_builtins(char **cmd, t_list *env_list);

/*
**	FILE - bin_paths.c
*/
int		is_path(char *cmd);
int		exec_from_path(char **cmd, t_list *env_list);

/*
**	FILE - bin_bins.c
*/
int		exec_from_bins(char **cmd, t_list *env_list);

/*
**	FILE - signals.c
*/
void	signal_handler(int signal_value);

typedef struct		s_global
{
	t_list	*env_list;
	t_list	*history;
	pid_t	pid;
	int		last_return;
}					t_global;

t_global	global;

typedef struct		s_env
{
	char	*name;
	char	*value;
}					t_env;

#endif
