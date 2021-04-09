/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:42:27 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 16:40:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft.h"

// FILE - parse.c
char	***parse(char *cmd);

// FILE - exec.c
int		exec(char ***cmds, char **envp);
int		exec_bin(char *path, char **args, char **envp);
char	*create_full_path(char *bin_path, char *cmd);

// FILE - main.c
int		env(char **envp);

// FILE - utils.c
int		get_strarr_size(char **arr);

// FILE - debug.c
void	dbg_display_stat_buff(struct stat stat_buff);

// FILE - prompt.c
void	prompt(void);

// BUILTINS - env
int		env(char **envp);

/*
**	FILE - utils_mem.c
*/
void	free_split(char **tab);
void	free_cmds(char ***cmds);

/*
**	FILE - bin_builtins.c
*/
int		is_builtin(char *cmd, char **envp);

/*
**	FILE - bin_paths.c
*/
int		is_path(char *cmd);
int		exec_from_path(char **cmd, char **envp);

/*
**	FILE - bin_bins.c
*/
int		exec_from_bins(char **cmd, char **envp);

#endif
