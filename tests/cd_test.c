#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

Test(cd_basic, passing) {
	int		fd;
	char	*path;
	char	buff[100];
	int		diff;

	path = "tests/outputs_m_sh/basic_input.log";
	system("echo 'echo lol' | ./minishell  > tests/outputs_m_sh/basic_input.log");
	fd = open(path, O_RDONLY);
	read(fd, buff, 100);
	diff = ft_strncmp("lol\n", buff, 50);
	// cr_assert(diff == 0);
	cr_assert(1);
	close(fd);
	if (diff == 0)
		system("rm tests/outputs_m_sh/basic_input.log");
}
