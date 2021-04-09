#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

Test(basic_input, basic_echo) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "lol";
	path = "tests/outputs_m_sh/basic_echo.log";
	system("echo -n 'echo -n lol' | ./minishell > tests/outputs_m_sh/basic_echo.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/basic_echo.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(basic_input, empty) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "";
	path = "tests/outputs_m_sh/empty.log";
	system("echo -n 'echo -n ' | ./minishell > tests/outputs_m_sh/empty.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/empty.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(basic_input, very_long_input) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "aertyuioopqsdfghjkllmwxcvbn123456789&éaertyuioopqsdfghjkllmwxcvbn123456789&é";
	path = "tests/outputs_m_sh/very_long_input.log";
	system("echo -n 'echo -n aertyuioopqsdfghjkllmwxcvbn123456789&éaertyuioopqsdfghjkllmwxcvbn123456789&é' | ./minishell > tests/outputs_m_sh/very_long_input.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/very_long_input.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}
