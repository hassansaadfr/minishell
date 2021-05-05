#ifndef CRITERION_H
#define CRITERION_H

typedef struct	s_cmd_test {
	char	*output_bash;
	char	*output_msh;
	char	*cmd_bash;
	char	*cmd_msh;

}				t_cmd_test;

t_cmd_test	*generate_cmds(char *test_name, char *cmd);
char		**compare_bash_msh(char *test_name, char *cmd);

#endif
