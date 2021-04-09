/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:42:27 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/09 17:57:08 by hsaadaou         ###   ########.fr       */
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

// FILE - utils.c
int		get_strarr_size(char **arr);
int		handle_errno(int err, char *binary, char *arg);

// FILE - debug.c
void	dbg_display_stat_buff(struct stat stat_buff);

// FILE - prompt.c
void	prompt(void);

// BUILTINS - env
int		env(char **envp);
int		builtin_cd(char **argv, char **env);

// FILE - utils_mem.c
void	free_split(char **tab);
void	free_cmds(char ***cmds);


#endif
