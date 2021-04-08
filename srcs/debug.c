#include "minishell.h"

void	dbg_display_stat_buff(struct stat stat_buff)
{
	printf("stat_buff.st_mode : %u\n\n", stat_buff.st_mode);
}
