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
# include <fcntl.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "constants.h"
# include "struct.h"

/*
**	FILE - main.c
*/
int				minishell(t_list *env_list);

/*
** FILE - parse.c
*/
char			***parse(char *cmd);

/*
** FILE - utils.c
*/
int				get_strarr_size(char **arr);

/*
**	FILE - debug.c
*/
void			dbg_display_stat_buff(struct stat stat_buff);
void			display_tokens(t_list *tokens);
void			display_splitted_cmd(t_list *cmd, int debug_i, char *type);
char			*enum_to_str(int type);
void			print_token_str(char *arg);

/*
**	FILE - debug2.c
*/

void			display_token_to_be_splitted(t_token *token, char **arg_split);
void			display_splitted_pipeline(t_pipeline *splitted_pipeline,
					int cmd_count);

/*
 **	FILE - prompt.c
 */
void			prompt(void);

/*
**	BUILTINS
*/
int				env(t_list *env_list);
int				unset(char *argv, t_list *env_list);
int				builtin_echo(char **argv, t_list *env_list);
int				builtin_cd(char **argv, t_list *env_list);
int				builtin_env(char **argv, t_list *env_list);
int				builtin_exit(char **argv, t_list *env_list);
int				builtin_export(char **argv, t_list *env_list);
int				builtin_pwd(char **argv, t_list *env_list);
int				builtin_unset(char **argv, t_list *env_list);
int				builtin_history(char **argv, t_list *env_list, t_list *history);

/*	FILE - utils_mem.c */
void			free_cmds(char ***cmds);
void			free_env(t_list **env_list);
void			*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);
void			free_token(void *content);
void			free_splitted_pipeline(t_pipeline *splitted_pipeline,
					int cmd_count);

/*
**	FILE - utils_env.c
*/
int				new_env(t_list *env_list, char *new_env);
t_list			*get_env(t_list *env_list, char *name);
int				edit_env(t_list *env_list, char *env);
int				delete_env(t_list *env_list, char *name);
char			*get_env_value(t_list *env_list, char *name);

/*
**	FILE - parse_env.c
*/
char			*parse_env_value(char *env);
char			*parse_env_name(char *env);
char			**list_to_array(t_list *env_list);
int				is_valid_env_name(char *name, char *binary);

/*
** FILE - exec.c
*/
int				execution(char **cmds, t_list *env_list, t_list *history);
int				process_is_parent(void);

/*
** FILE redirections.c
*/
int				perform_redirections(t_list *redirs);

/*
** FILE perform_execution.c
*/
char			**token_list_to_array(t_list *token_list);
int				search_bin(char **cmd, t_list *env_list);
int				perform_execution(t_list *redirs, t_list *tokens,
					t_list *env_list);

/*
**	FILE - utils_mem_env.c
*/
t_list			*init_env(char **envp);
t_list			*init_env_node(char *env);
void			free_env_node(void *ptr);

/*
**	FILE - bin_builtins.c
*/
int				is_builtin(char **cmd);
int				exec_from_builtins(char **cmd, t_list *env_list,
					t_list	*history);

/*
**	FILE - bin_paths.c
*/
int				is_path(char *cmd);
int				exec_from_path(char **cmd, t_list *env_list);
t_path			get_path_type(char *str);

/*
**	FILE - bin_bins.c
*/
int				exec_from_bins(char **cmd, t_list *env_list);

/*
**	FILE - signals.c
*/
void			signal_handling_register(void);
void			sigint_handler(int signal_value);
void			sigquit_handler(int signal_value);

/*
**	FILE - termios.c
*/
struct termios	enable_raw_mode(void);
void			disable_raw_mode(struct termios orig_termios);

/*
**	FILE - initializations.c
*/
int				init_buff_and_history(t_input *buff, t_list **history);
int				init_termcaps(t_list *env_list);
size_t			init_parse_struct(t_parse *p, char *line);
void			init_expand_struct(t_expand *exp, t_token *token);

/*
**	FILE - utils_input.c
*/
int				is_ctrl_keys(char c, t_input *buff, t_list *history,
					struct termios orig_termios);
int				arrow_value(void);
char			ctrl_value(char c);
int				not_empty(char *buffer);

/*
**	FILE - termcaps.c
*/
int				put_termcap(int c);
void			exec_termcap(char *termcap_name);
void			delete_char(t_input *buff);
void			clear_line(t_input *buff);

/*
**	FILE - input.c
*/
char			read_key(void);
int				process_key(t_input *buff);
int				expand_buffers(t_input *buff);
void			write_buffer(t_input *buff, t_list *history,
					struct termios orig_termios);
void			move_cursor_back(void);

/*
**	FILE - history.c
*/
void			display_history(t_list *hist);
void			add_to_history(t_input *buff, t_list **history);
void			exec_up_arrow(t_input *buff, t_list *history);
void			exec_down_arrow(t_input *buff);
void			change_input_str(int arrow, t_input *buff, t_list *history);

/*
**	FILE - tokenizer.c
*/
t_list			*parsing(char *line);
void			display_tokens(t_list *tokens);
void			free_token(void *token);
int				add_to_tokens_list(t_parse *p);

/*
**	FILE - utils_quoting.c
*/
void			backslash(t_parse *p, char **line);
void			s_quote(t_parse *p, char **line);
void			d_quote(t_parse *p, char **line);
void			dollar_in_d_quote(t_parse *p, char **line);
void			quoting_wrapper(t_parse *p, char **line);

/*
**	FILE - utils_d_quote.c
*/
void			open_d_quote(t_parse *p, char **line);
void			close_d_quote(t_parse *p, char **line);
void			dollar_in_d_quote(t_parse *p, char **line);

/*
**	FILE - utils_parsing.c
*/
int				metachar(t_parse *p, char **line);
int				is_metachar(char c);
int				space_or_null(t_parse *p);
int				d_quote_conditions(t_parse *p, char **line);

/*
**	FILE - types.c
*/
int				typing(t_parse *p);
int				is_redir(enum e_types type);
int				is_redir_or_fd(t_list *node);

/*
**	FILE - parsing_errors.c
*/
t_list			*check_parsing_errors(t_parse *p, int ret_mtc_or_spc);

/*
**	FILE - utils_exclusions.c
*/
int				smc_exclusions(t_token *last_token);
int				pipe_exclusions(t_token *last_token);
int				redirs_exclusions(t_token *last_token, int curr_type);
int				newline_exclusions(t_list *last_node);

/*
**	FILE - exec2.c
*/
int				executing(t_list *tokens, t_list *env, t_list *history);
void			reformat(t_list *list);

/*
**	FILE - rearrange_lists.c
*/
t_list			*isolate_indpdt_cmd(t_list **tokens);
t_list			*isolate_redirs(t_list **args);

/*
**	FILE - utils_expansion.c
*/
int				token_is(int wanted_type, t_token *token);
void			*arg_contains(char wanted_char, char *arg);
int				token_has_empty_arg(t_token *token);
void			remove_empty_tokens(t_list **args);

/*
**	FILE - expansion.c
*/
t_list			*expand_redirs(t_list **redirs, t_list *env_list);
t_list			*expand_args(t_list **args, t_list *env_list);
void			expand_in_token(t_token *token, t_list *env_list,
					char *dollar_pos);
t_list			*expansion(t_list *cmd, t_list *env_list);

/*
**	FILE - utils_concat.c
*/
char			*concat_expansion(char *new_arg, char *key_pos,
					t_list *env_list);
char			*concat_remaining(char *new_arg, char *remaining);
void			prepare_concat(char **dollar_pos, char **new_arg,
					char **remaining, char *tmp_c);
char			*dup_expansion_value(char *key_pos, t_list *env_list);
void			quoting_to_neg(char **expansion);

/*
**	FILE - path_utils.c
*/
char			*get_binary_path(char *cmd, t_list *env_list);

/*
**	FILE - errors.c
*/
void			print_err(char *binary, char *arg, char *err);
void			print_err_with_quote(char *binary, char *arg, char *err);
int				return_err_msg(char *problem_pos, char *err_msg, int err);

/*
**	FILE - minishell_entry.c
*/
int				minishell(t_list *env_list);
int				minishell_init(struct termios *orig_termios,
					t_list *env_list);
int				minishell_tty(t_list *env_list);
int				minishell_non_tty(t_list *env_list);

/*	FILE - utils_pipeline.c */
int				is_pipeline(t_list *indpdt_cmd);
void			split_pipeline(t_list *pipeline,
					t_pipeline *splitted_pipeline);
void			init_splitted_pipeline(t_pipeline *splitted_pipeline,
					int cmd_count);
int				count_pipes(t_list *pipeline);

/*	FILE - pipe.c */
int				execute_pipeline(t_list *pipeline, t_list *env_list);
int				display_err_ret_err(char *problem_pos, char *err_msg, int err);

/*	FILE - utils_fds.c */
int				backup_std(int *old_fds);
int				restore_fds(int *old_fds);
int				init_pipe_struct(t_fds *p, int cmd_count, t_list *env_list);

/*	FILE - expand_pipeline.c */
void			expand_pipeline(t_pipeline *pipeline, int cmd_count,
					t_list *env_list);

/*	FILE - pipeline_redirs.c */
int				perform_pipeline_redirections(t_list *redirs, int *in_out_tbc);

/*	FILE - exec_for_pipeline.c */
int				one_pipe_exec(char **cmds, t_list *env_list, t_list *history);

/*
** FILE - init-shlvl_and_path.c
*/
void			init_path_and_shlvl(t_list **env_list);

/*	FILE - cursor_utils.c */
int				get_cursor_pos(int *y, int *x);
int				get_line_width(void);
void			erase_input(t_input *buff, struct winsize w,
					char *pwd_val);

#endif
