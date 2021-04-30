#include <criterion/criterion.h>
#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

typedef struct	s_cmd_test {
	char	*output_bash;
	char	*output_msh;
	char	*cmd_bash;
	char	*cmd_msh;

}				t_cmd_test;

t_cmd_test	*generate_cmds(char *test_name, char *cmd)
{
	t_cmd_test	*cmds;

	cmds = malloc(sizeof(t_cmd_test));
	cmds->output_bash = ft_strjoin(ft_strjoin(" > tests/outputs_bash/", test_name), ".log");
	cmds->output_msh = ft_strjoin(ft_strjoin(" > tests/outputs_m_sh/", test_name), ".log");
	cmds->cmd_bash = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("echo -n ", "\""), cmd), "\""), " | bash --posix"), cmds->output_bash);
	cmds->cmd_msh = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("echo -n ", "\""), cmd), "\""), " | ./minishell"), cmds->output_msh);
	return (cmds);
}

char	**compare_bash_msh(char *test_name, char *cmd)
{
	t_cmd_test	*cmds;
	int			fd_bash;
	int			fd_msh;
	int			readed;
	char		expected[1000];
	char		returned[1000];
	char		**outputs;

	outputs = malloc(sizeof(char*) * 3);
	outputs[2] = 0;
	cmds = generate_cmds(test_name, cmd);
	system(cmds->cmd_bash);
	system(cmds->cmd_msh);
	fd_bash = open(cmds->output_bash + 3, O_RDONLY);
	fd_msh = open(cmds->output_msh + 3, O_RDONLY);
	readed = read(fd_bash, expected, 1000);
	expected[readed] = 0;
	readed = read(fd_msh, returned, 1000);
	returned[readed] = 0;
	outputs[0] = ft_strdup(returned);
	outputs[1] = ft_strdup(expected);
	close(fd_bash);
	close(fd_msh);
	return (outputs);
}

Test(echo_suite, echo_basic) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_basic", "echo \"123\"");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_basic_new_line) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_basic_new_line", "echo -n \"123\"");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}


Test(echo_suite, echo_empty) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_empty", "echo ");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_empty_new_line) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_empty_new_line", "echo -n");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_multiple_arg) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_multiple_arg", "echo hello bonjour 1 2 3 4 5 6 58 7841 48 48 45 48");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_multiple_arg_nl) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_multiple_arg_nl", "echo -n hello bonjour 1 2 3 4 5 6 58 7841 48 48 45 48");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_spaces) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_spaces", "echo                                        ");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_spaces_nl) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_spaces_nl", "echo -n                                        ");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_spaces_between_args) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_spaces_between_args", "echo -n                t                     l   ");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}

Test(echo_suite, echo_tricky) {
	char	**outputs;
	int		diff;

	diff = -1;
	outputs = compare_bash_msh("echo_tricky", "echo echo echo ls pwd");
	diff = ft_strncmp(outputs[0], outputs[1], 1000);
	cr_assert(diff == 0, "EXPECTED:\t%s\nRETURNED:\t%s\n", outputs[1], outputs[0]);
}
