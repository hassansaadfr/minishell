#include <criterion/criterion.h>
#include "minishell.h"
#include "criterion.h"
#include <unistd.h>
#include <fcntl.h>

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
