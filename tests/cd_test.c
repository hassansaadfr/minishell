#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

Test(cd_suite, directory_dont_exist) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "minishell: cd: toto: No such file or directory";
	path = "tests/outputs_m_sh/cd_directory_dont_exist.log";
	system("echo -n 'cd toto ' | ./minishell 2> tests/outputs_m_sh/cd_directory_dont_exist.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_directory_dont_exist.log");
	else
		printf("+++++\nYour return:\t\"%s\"\nExpected:\t\"%s\"\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd_suite, root_dir) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "";
	path = "tests/outputs_m_sh/cd_root_dir.log";
	system("echo -n 'cd / ' | ./minishell > tests/outputs_m_sh/cd_root_dir.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_root_dir.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd_suite, parent_dir) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "";
	path = "tests/outputs_m_sh/cd_parent_dir.log";
	system("echo -n 'cd .. ' | ./minishell > tests/outputs_m_sh/cd_parent_dir.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_parent_dir.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd_suite, parent_tricky) {
	int		fd;
	char	*path;
	int		diff;
	char	expected[PATH_MAX];
	char	*file;

	getcwd(expected, PATH_MAX);
	path = "tests/outputs_m_sh/cd_parent_tricky.log";
	system("mkdir -p test1/test2/test3");
	system("echo -n 'cd test1/test2/test3/../../.. ; pwd' | ./minishell > tests/outputs_m_sh/cd_parent_tricky.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_parent_tricky.log");
	else
	{
		printf("test: parent_tricky\n");
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	}
	system("rm -rf test1");
	cr_assert(diff == 0);
}

Test(cd_suite, the_root_parent) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "/";
	path = "tests/outputs_m_sh/cd_the_root_parent.log";
	system("echo -n 'cd /../.. ; pwd' | ./minishell > tests/outputs_m_sh/cd_the_root_parent.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_the_root_parent.log");
	else
	{
		printf("test: the_root_parent\n");
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	}
	cr_assert(diff == 0);
}

Test(cd_suite, acces_denied) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "minishell: cd: /toto: Permission denied";
	path = "tests/outputs_m_sh/cd_acces_denied.log";
	system("mkdir /toto; chmod 000 /toto");
	system("echo -n 'cd /toto' | sudo -u user1 ./minishell 2> tests/outputs_m_sh/cd_acces_denied.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_acces_denied.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd_suite, too_many_args) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "minishell: cd: Argument list too long";
	path = "tests/outputs_m_sh/cd_too_many_args.log";
	system("echo -n 'cd toto titi' | ./minishell 2> tests/outputs_m_sh/cd_too_many_args.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_too_many_args.log");
	else
		printf("+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
	cr_assert(diff == 0);
}

Test(cd_suite, cd_empty_arg) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = getenv("HOME");
	path = "tests/outputs_m_sh/cd_empty_arg.log";
	system("echo -n 'cd ; pwd' | ./minishell > tests/outputs_m_sh/cd_empty_arg.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_empty_arg.log");
	cr_assert(diff == 0, "+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
}

Test(cd_suite, cd_home_minus) {
	int		fd;
	char	*path;
	int		diff;
	char	*expected;
	char	*file;

	expected = "/";
	path = "tests/outputs_m_sh/cd_home_minus.log";
	system("echo -n 'cd / && cd - ; pwd' | ./minishell > tests/outputs_m_sh/cd_home_minus.log");
	fd = open(path, O_RDONLY);
	get_next_line(fd, &file);
	diff = ft_strncmp(expected, file, 100);
	close(fd);
	if (diff == 0)
		system("rm -f tests/outputs_m_sh/cd_home_minus.log");
	cr_assert(diff == 0, "+++++\nYour return: %s\nExpected: %s\n+++++\n", file, expected);
}
