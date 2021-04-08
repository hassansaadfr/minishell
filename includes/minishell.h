/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:42:27 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/04/08 14:29:20 by user42           ###   ########.fr       */
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

// FILE - main.c
int		env(char **envp);

// FILE - utils.c
int		get_strarr_size(char **arr);

// FILE - debug.c
void	dbg_display_stat_buff(struct stat stat_buff);


#endif
