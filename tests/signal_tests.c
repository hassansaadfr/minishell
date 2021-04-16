#include <fcntl.h>
#include <criterion/criterion.h>
#include "minishell.h"
#include <sys/types.h>

Test(signal_suite, toto, .signal = SIGINT)
{
	char	buff[100];
	errno = 0;
	system("./minishell &");
	system("pidof minishell > pidfile");
	int fd = open("pidfile", O_RDONLY);
	int readed = read(fd, buff, 100);
	buff[readed] = 0;
	kill(ft_atoi(buff), SIGINT);
	struct stat sts;
	close(fd);
	system("rm pidfile");
	if (stat(ft_strjoin("/proc/", buff), &sts) == -1 && errno == ENOENT) {
		cr_expect(0);
	}
	cr_expect(1);
}
