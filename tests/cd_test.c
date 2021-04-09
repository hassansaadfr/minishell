#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

Test(cd, directory_dont_exist) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "minishell: No such file or directory";
	path = "tests/outputs_m_sh/directory_dont_exist.log";
	system("echo -n 'cd toto ' | ./minishell > tests/outputs_m_sh/directory_dont_exist.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/directory_dont_exist.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd, root_dir) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "";
	path = "tests/outputs_m_sh/root_dir.log";
	system("echo -n 'cd / ' | ./minishell > tests/outputs_m_sh/root_dir.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/root_dir.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd, parent_dir) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "";
	path = "tests/outputs_m_sh/parent_dir.log";
	system("echo -n 'cd .. ' | ./minishell > tests/outputs_m_sh/parent_dir.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/parent_dir.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd, parent_tricky) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "/";
	path = "tests/outputs_m_sh/parent_tricky.log";
	system("echo -n 'cd srcs/../.. ; pwd' | ./minishell > tests/outputs_m_sh/parent_tricky.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/parent_tricky.log");
	else
	{
		printf("test: parent_tricky\n");
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	}
	cr_assert(diff == 0);
}

Test(cd, the_root_parent) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "/";
	path = "tests/outputs_m_sh/the_root_parent.log";
	system("echo -n 'cd /../.. ; pwd' | ./minishell > tests/outputs_m_sh/the_root_parent.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/the_root_parent.log");
	else
	{
		printf("test: the_root_parent\n");
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	}
	cr_assert(diff == 0);
}

Test(cd, acces_denied) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "minishell: Permission denied";
	path = "tests/outputs_m_sh/acces_denied.log";
	system("mkdir /toto; chmod 000 /toto");
	system("echo -n 'cd /toto' | sudo -u user1 ./minishell > tests/outputs_m_sh/acces_denied.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/acces_denied.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}
