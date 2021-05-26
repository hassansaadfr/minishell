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
# include <signal.h>
# include <limits.h>

# include "libft.h"
# include "constants.h"
# include "struct.h"

/*
**	FILE - main.c
*/
//int			minishell(t_termios orig_termios);
//int			minishell(void);
int			minishell(t_list *env_list);

/*
** FILE - parse.c
*/
char		***parse(char *cmd);

/*
** FILE - utils.c
*/
int			get_strarr_size(char **arr);
int			handle_errno(int err, char *binary, char *arg);

/*
**	FILE - debug.c
*/
void		dbg_display_stat_buff(struct stat stat_buff);
void		display_tokens(t_list *tokens);
void		display_splitted_cmd(t_list *cmd, int debug_i, char *type);
char		*enum_to_str(int type);

/*
**	FILE - prompt.c
*/
void		prompt(void);

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
int			builtin_history(char **argv, t_list *env_list, t_list *history);

/*
**	FILE - utils_mem.c
*/
void		free_split(char **splitted);
void		free_cmds(char ***cmds);
void		free_env(t_list **env_list);
void		*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);
void		free_token(void *content);

/*
**	FILE - utils_env.c
*/
int			new_env(t_list *env_list, char *new_env);
t_list		*get_env(t_list *env_list, char *name);
int			edit_env(t_list *env_list, char *env);
int			delete_env(t_list *env_list, char *name);
char		*get_env_value(t_list *env_list, char *name);

/*
**	FILE - parse_env.c
*/
char		*parse_env_value(char *env);
char		*parse_env_name(char *env);
char		**list_to_array(t_list *env_list);
int			is_valid_env_name(char *name, char *binary);

/*
** FILE - exec.c
*/
int			execution(char **cmds, t_list *env_list, t_list *history);

/*
**	FILE - utils_mem_env.c
*/

t_list		*init_env(char **envp);
t_list		*init_env_node(char *env);
void		free_env_node(void *ptr);

/*
**	FILE - bin_builtins.c
*/
int			is_builtin(char **cmd);
int			exec_from_builtins(char **cmd, t_list *env_list, t_list	*history);

/*
**	FILE - bin_paths.c
*/
int			is_path(char *cmd);
int			exec_from_path(char **cmd, t_list *env_list);

/*
**	FILE - bin_bins.c
*/
int			exec_from_bins(char **cmd, t_list *env_list);

/*
**	FILE - signals.c
*/
void		sigint_handler(int signal_value);

/*
**	FILE - termios.c
*/
t_termios	enable_raw_mode(void);
void		disable_raw_mode(t_termios orig_termios);

/*
**	FILE - initializations.c
*/
int			init_buff_and_history(t_input *buff, t_list **history);
int			init_termcaps(t_list *env_list);
size_t		init_parse_struct(t_parse *p, char *line);
void		init_expand_struct(t_expand *exp, t_token *token);

/*
**	FILE - utils_input.c
*/
int			is_ctrl_keys(char c, int *stop, t_input *buff, t_list *history);
int			arrow_value(void);
char		ctrl_value(char c);
int			not_empty(char *buffer);

/*
**	FILE - termcaps.c
*/
int			put_termcap(int c);
void		exec_termcap(char *termcap_name);
void		delete_char(t_input *buff);
void		clear_line(t_input *buff);

/*
**	FILE - buffer.c
*/
char		read_key(void);
int			process_key(t_input *buff);
int			expand_buffers(t_input *buff);
int			write_buffer(int *stop, t_input *buff, t_list *history);

/*
**	FILE - history.c
*/
void		display_history(t_list *hist);
int			add_to_history(t_input *buff, t_list **history);
void		exec_up_arrow(t_input *buff, t_list *history);
void		exec_down_arrow(t_input *buff);
void		change_input_str(int arrow, t_input *buff, t_list *history);

/*
**	FILE - tokenizer.c
*/
t_list		*parsing(char *line);
void		display_tokens(t_list *tokens);
void		free_token(void *token);
int			add_to_tokens_list(t_parse *p);

/*
**	FILE - utils_quoting.c
*/
void		backslash(t_parse *p, char **line);
void		s_quote(t_parse *p, char **line);
void		d_quote(t_parse *p, char **line);
void		dollar_in_d_quote(t_parse *p, char **line);

/*
**	FILE - utils_d_quote.c
*/
void		open_d_quote(t_parse *p, char **line);
void		close_d_quote(t_parse *p, char **line);
void		dollar_in_d_quote(t_parse *p, char **line);

/*
**	FILE - utils_parsing.c
*/
int			metachar(t_parse *p, char **line);
int			is_metachar(char c);
int			space_or_null(t_parse *p);
int			d_quote_conditions(t_parse *p, char **line);

/*
**	FILE - types.c
*/
int			typing(t_parse *p);
int			is_redir(enum e_types type);
int			is_redir_or_fd(t_list *node);

/*
**	FILE - parsing_errors.c
*/
t_list		*check_parsing_errors(t_parse *p, int ret_mtc_or_spc);

/*
**	FILE - utils_exclusions.c
*/
int			smc_exclusions(t_token *last_token);
int			pipe_exclusions(t_token *last_token);
int			redirs_exclusions(t_token *last_token, int curr_type);
int			newline_exclusions(t_list *last_node);

/*
**	FILE - exec2.c
*/
int			executing(t_list *tokens, t_list *env, t_list *history);

/*
**	FILE - rearrange_lists.c
*/
t_list		*isolate_indpdt_cmd(t_list **tokens);
t_list		*isolate_redirs(t_list **args);

/*
**	FILE - utils_expansion.c
*/
int			token_is(int wanted_type, t_token *token);
void		*arg_contains(char wanted_char, char *arg);

/*
**	FILE - expansion.c
*/
t_list		*expand_redirs(t_list **redirs, t_list *env_list);
t_list		*expansion(t_list *cmd, t_list *env_list);

/*
**	FILE - expansion.c
*/
char		*get_binary_path(char *cmd, t_list *env_list);

/*
**	FILE - expansion.c
*/
void		print_err(char *binary, char *arg, char *err);

#endif
