#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

Test(basic_input, basic_echo) {
	int		fd;
	char	*path;
	char	buff[100];
	int		diff;
	char	*expected;

	expected = "lol\n";
	path = "tests/outputs_m_sh/basic_input.log";
	system("echo 'echo -n lol' | ./minishell > tests/outputs_m_sh/basic_input.log");
	fd = open(path, O_RDONLY);
	read(fd, buff, 100);
	diff = ft_strncmp(expected, buff, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/basic_input.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", buff, expected);
	cr_assert(diff == 0);
}

Test(basic_input, empty) {
	int		fd;
	char	*path;
	char	buff[100];
	int		diff;
	char	*expected;

	expected = "";
	path = "tests/outputs_m_sh/basic_input.log";
	system("echo 'echo -n' | ./minishell > tests/outputs_m_sh/basic_input.log");
	fd = open(path, O_RDONLY);
	read(fd, buff, 100);
	diff = ft_strncmp(expected, buff, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/basic_input.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", buff, expected);
	cr_assert(diff == 0);
}

