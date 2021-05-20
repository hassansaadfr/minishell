#include <criterion/criterion.h>
#include "minishell.h"
#include "criterion.h"
#include <fcntl.h>

Test(exit_suite_msg, exit_arg_cmp_no_arg)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit | ./minishell 2> ./tests/outputs_m_sh/exit_arg_cmp_no_arg.log");
	system("echo exit | bash --posix 2> ./tests/outputs_bash/exit_arg_cmp_no_arg.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_cmp_no_arg.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_cmp_no_arg.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_empty(output_bsh);
	cr_assert_str_empty(output_msh);
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_cmp_no_arg.log ./tests/outputs_bash/exit_arg_cmp_no_arg.log");
}

Test(exit_suite_msg, exit_arg_cmp_non_numeric)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit bonjour | ./minishell 2> ./tests/outputs_m_sh/exit_arg_cmp_non_numeric.log");
	system("echo exit bonjour | bash --posix 2> ./tests/outputs_bash/exit_arg_cmp_non_numeric.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_cmp_non_numeric.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_cmp_non_numeric.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_cmp_non_numeric.log ./tests/outputs_bash/exit_arg_cmp_non_numeric.log");
}

Test(exit_suite_msg, exit_arg_cmp_non_numeric_multiple)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit a b | ./minishell 2> ./tests/outputs_m_sh/exit_arg_cmp_non_numeric_multiple.log");
	system("echo exit a b | bash --posix 2> ./tests/outputs_bash/exit_arg_cmp_non_numeric_multiple.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_cmp_non_numeric_multiple.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_cmp_non_numeric_multiple.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_cmp_non_numeric_multiple.log ./tests/outputs_bash/exit_arg_cmp_non_numeric_multiple.log");
}

Test(exit_suite_msg, exit_arg_cmp_non_numeric_and_num)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit a 4 | ./minishell 2> ./tests/outputs_m_sh/exit_arg_cmp_non_numeric_and_num.log");
	system("echo exit a 4 | bash --posix 2> ./tests/outputs_bash/exit_arg_cmp_non_numeric_and_num.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_cmp_non_numeric_and_num.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_cmp_non_numeric_and_num.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_cmp_non_numeric_and_num.log ./tests/outputs_bash/exit_arg_cmp_non_numeric_and_num.log");
}

Test(exit_suite_msg, exit_arg_cmp_non_numeric_and_num2)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit 4 a | ./minishell 2> ./tests/outputs_m_sh/exit_arg_cmp_non_numeric_and_num2.log");
	system("echo exit 4 a | bash --posix 2> ./tests/outputs_bash/exit_arg_cmp_non_numeric_and_num2.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_cmp_non_numeric_and_num2.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_cmp_non_numeric_and_num2.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_cmp_non_numeric_and_num2.log ./tests/outputs_bash/exit_arg_cmp_non_numeric_and_num2.log");
}

Test(exit_suite_msg, exit_arg_cmp_to_much_num)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit 4 4 | ./minishell 2> ./tests/outputs_m_sh/exit_arg_cmp_to_much_num.log");
	system("echo exit 4 4 | bash --posix 2> ./tests/outputs_bash/exit_arg_cmp_to_much_num.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_cmp_to_much_num.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_cmp_to_much_num.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_cmp_to_much_num.log ./tests/outputs_bash/exit_arg_cmp_to_much_num.log");
}

Test(exit_suite_msg, exit_arg_minus)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit - | ./minishell 2> ./tests/outputs_m_sh/exit_arg_minus.log");
	system("echo exit - | bash --posix 2> ./tests/outputs_bash/exit_arg_minus.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_minus.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_minus.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_minus.log ./tests/outputs_bash/exit_arg_minus.log");
}

Test(exit_suite_msg, exit_arg_double_minus)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit -- | ./minishell 2> ./tests/outputs_m_sh/exit_arg_double_minus.log");
	system("echo exit -- | bash --posix 2> ./tests/outputs_bash/exit_arg_double_minus.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_double_minus.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_double_minus.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert(ft_strlen(output_bsh) == 0 && ft_strlen(output_msh) == 0);
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_double_minus.log ./tests/outputs_bash/exit_arg_double_minus.log");
}

Test(exit_suite_msg, exit_arg_plus)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit + | ./minishell 2> ./tests/outputs_m_sh/exit_arg_plus.log");
	system("echo exit + | bash --posix 2> ./tests/outputs_bash/exit_arg_plus.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_plus.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_plus.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_plus.log ./tests/outputs_bash/exit_arg_plus.log");
}

Test(exit_suite_msg, exit_arg_double_plus)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit ++ | ./minishell 2> ./tests/outputs_m_sh/exit_arg_double_plus.log");
	system("echo exit ++ | bash --posix 2> ./tests/outputs_bash/exit_arg_double_plus.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_double_plus.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_double_plus.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_double_plus.log ./tests/outputs_bash/exit_arg_double_plus.log");
}

Test(exit_suite_msg, exit_arg_arobase)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit @ | ./minishell 2> ./tests/outputs_m_sh/exit_arg_arobase.log");
	system("echo exit @ | bash --posix 2> ./tests/outputs_bash/exit_arg_arobase.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_arobase.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_arobase.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_arobase.log ./tests/outputs_bash/exit_arg_arobase.log");
}

Test(exit_suite_msg, exit_arg_num_and_non_num)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit 0a | ./minishell 2> ./tests/outputs_m_sh/exit_arg_num_and_non_num.log");
	system("echo exit 0a | bash --posix 2> ./tests/outputs_bash/exit_arg_num_and_non_num.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_num_and_non_num.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_num_and_non_num.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_num_and_non_num.log ./tests/outputs_bash/exit_arg_num_and_non_num.log");
}

Test(exit_suite_msg, exit_arg_num_and_non_num2)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[1000];
	char output_bsh[1000];

	system("echo exit a0 | ./minishell 2> ./tests/outputs_m_sh/exit_arg_num_and_non_num2.log");
	system("echo exit a0 | bash --posix 2> ./tests/outputs_bash/exit_arg_num_and_non_num2.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_num_and_non_num2.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_num_and_non_num2.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_assert_str_eq(ft_strchr(output_msh, ':'), ft_strchr(output_bsh, ':'));
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_num_and_non_num2.log ./tests/outputs_bash/exit_arg_num_and_non_num2.log");
}
