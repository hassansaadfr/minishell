#include <criterion/criterion.h>
#include "minishell.h"
#include "criterion.h"
#include <fcntl.h>

// Test(exit_suite, exit_basic_loop)
// {
// 	int fd_msh = -1;
// 	int fd_bsh = -1;
// 	int readed = 0;
// 	char output_msh[100];
// 	char output_bsh[100];

// 	for (int i = -1000; i < 1001; i++)
// 	{
// 		system(ft_strjoin(ft_strjoin("export ITER=", ft_itoa(i)), "&& echo exit $ITER | ./minishell ; echo $? > ./tests/outputs_m_sh/exit_basic.log"));
// 		system(ft_strjoin(ft_strjoin("export ITER=", ft_itoa(i)), "&& echo exit $ITER | bash --posix ; echo $? > ./tests/outputs_bash/exit_basic.log"));
// 		fd_msh = open("tests/outputs_m_sh/exit_basic.log", O_RDONLY);
// 		fd_bsh = open("tests/outputs_bash/exit_basic.log", O_RDONLY);
// 		readed = read(fd_bsh, output_bsh, 100);
// 		output_bsh[readed] = 0;
// 		readed = read(fd_msh, output_msh, 100);
// 		output_msh[readed] = 0;
// 		close(fd_bsh);
// 		close(fd_msh);
// 		system("rm ./tests/outputs_m_sh/exit_basic.log ./tests/outputs_bash/exit_basic.log");
// 		cr_expect(ft_strncmp(output_bsh, output_msh, 5) == 0, "expected %s returned %s", output_bsh, output_msh);
// 	}
// }

Test(exit_suite, exit_too_much_args)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[100];
	char output_bsh[100];

	system("echo exit 1 2 3 | ./minishell ; echo $? > ./tests/outputs_m_sh/exit_too_much_args.log");
	system("echo exit 1 2 3 | bash --posix ; echo $? > ./tests/outputs_bash/exit_too_much_args.log");
	fd_msh = open("tests/outputs_m_sh/exit_too_much_args.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_too_much_args.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_too_much_args.log ./tests/outputs_bash/exit_too_much_args.log");
	cr_expect(ft_strncmp(output_bsh, output_msh, 5) == 0, "expected %s returned %s", output_bsh, output_msh);
}

Test(exit_suite, exit_arg_not_num)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[100];
	char output_bsh[100];

	system("echo exit bonjour | ./minishell ; echo $? > ./tests/outputs_m_sh/exit_arg_not_num.log");
	system("echo exit bonjour | bash --posix ; echo $? > ./tests/outputs_bash/exit_arg_not_num.log");
	fd_msh = open("tests/outputs_m_sh/exit_arg_not_num.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_arg_not_num.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_expect(ft_strncmp(output_bsh, output_msh, 5) == 0, "expected %s returned %s", output_bsh, output_msh);
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_arg_not_num.log ./tests/outputs_bash/exit_arg_not_num.log");
}

Test(exit_suite, exit_no_arg)
{
	int fd_msh = -1;
	int fd_bsh = -1;
	int readed = 0;
	char output_msh[100];
	char output_bsh[100];

	system("echo exit | ./minishell ; echo $? > ./tests/outputs_m_sh/exit_no_arg.log");
	system("echo exit | bash --posix ; echo $? > ./tests/outputs_bash/exit_no_arg.log");
	fd_msh = open("tests/outputs_m_sh/exit_no_arg.log", O_RDONLY);
	fd_bsh = open("tests/outputs_bash/exit_no_arg.log", O_RDONLY);
	readed = read(fd_bsh, output_bsh, 100);
	output_bsh[readed] = 0;
	readed = read(fd_msh, output_msh, 100);
	output_msh[readed] = 0;
	cr_expect(ft_strncmp(output_bsh, output_msh, 5) == 0, "expected %s returned %s", output_bsh, output_msh);
	close(fd_bsh);
	close(fd_msh);
	system("rm ./tests/outputs_m_sh/exit_no_arg.log ./tests/outputs_bash/exit_no_arg.log");
}
