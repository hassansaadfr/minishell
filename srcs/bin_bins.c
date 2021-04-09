#include "minishell.h"

char 	*which_bin_fld(char *bin, char **bin_paths)
{
	char 			*path;
	int				i;
	struct stat		stat_buff;
	int				ret_stat;

	errno = 0;
    i = 0;
    ret_stat = -1;
    while (bin_paths[i] && ret_stat != 0)
    {
        path = create_full_path(bin_paths[i], bin);
		// CHECK create_full_path() RETURN 
        ret_stat = stat(path, &stat_buff);
        // CHECK stat() RETURN
        if (ret_stat)
            free(path);
        i++;
    }
	if (ret_stat == 0)
		return (path);
	else
		// NOT FOUND, errno set
		return (NULL);
}

int		exec_from_bins(char **cmd, char **envp)
{
	char			*path;
	char			**bin_paths;

	errno = 0;
	path = getenv("PATH");					// NULL IS NO MATCH
	// CHECK getenv() RETURN
	bin_paths = ft_split(path, ':');		// NULL IS ALLOC REFUSED
	// CHECK ft_split() RETURN 
	path = which_bin_fld(cmd[0], bin_paths);
	// CHECK which_bin_fld() RETURN			// NULL IF NOT FOUND
	free_split(bin_paths);
	if (path)
	{
		exec_bin(path, cmd, envp);
		free(path);
	}
	return (0);
}
