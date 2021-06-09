#include <criterion/criterion.h>
#include "minishell.h"
#include "criterion.h"
#include <unistd.h>
#include <fcntl.h>

t_cmd_test	*generate_cmds(char *test_name, char *cmd)
{
	t_cmd_test	*cmds;

	cmds = malloc(sizeof(t_cmd_test));
	cmds->output_bash = ft_strjoin(ft_strjoin(" > tests/outputs_bash/", test_name), ".log");
	cmds->output_msh = ft_strjoin(ft_strjoin(" > tests/outputs_m_sh/", test_name), ".log");
	cmds->cmd_bash = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("echo -n ", "\""), cmd), "\""), " | bash --posix"), cmds->output_bash);
	cmds->cmd_msh = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("echo -n ", "\""), cmd), "\""), " | ./minishell"), cmds->output_msh);
	return (cmds);
}

char	**compare_bash_msh(char *test_name, char *cmd)
{
	t_cmd_test	*cmds;
	int			fd_bash;
	int			fd_msh;
	int			readed;
	char		expected[1000];
	char		returned[1000];
	char		**outputs;

	outputs = malloc(sizeof(char *) * 3);
	outputs[2] = 0;
	cmds = generate_cmds(test_name, cmd);
	system(cmds->cmd_bash);
	system(cmds->cmd_msh);
	fd_bash = open(cmds->output_bash + 3, O_RDONLY);
	fd_msh = open(cmds->output_msh + 3, O_RDONLY);
	readed = read(fd_bash, expected, 1000);
	expected[readed] = 0;
	readed = read(fd_msh, returned, 1000);
	returned[readed] = 0;
	outputs[0] = ft_strdup(returned);
	outputs[1] = ft_strdup(expected);
	close(fd_bash);
	close(fd_msh);
	return (outputs);
}
