#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

static char		**init_dummy_arrstr(void)
{
	char	**out;
	char	*word1 = "NAME=MINISHELL";
	char	*word2 = "KIND=SHELL";
	char	*word3 = "FOO=BAR";

	out = malloc(sizeof(char *) * (3 + 1));
	out[0] = ft_strdup(word1);
	out[1] = ft_strdup(word2);
	out[2] = ft_strdup(word3);
	out[3] = NULL;
	return (out);
}

static t_list	*test_init_env(void)
{
	t_list	*env_list;
	char	**env;

	env = init_dummy_arrstr();
	env_list = init_env(env);
	return (env_list);
}

Test(unset_suite, unset_basic_exist) {
	t_list	*env_list;
	int		is_unset;

	env_list = test_init_env();
	is_unset = unset("KIND", env_list);
	cr_assert(get_env(env_list, "KIND") == NULL);
	cr_assert(is_unset == 1);
	free_env(&env_list);
}

Test(unset_suite, unset_basic_undefined) {
	t_list	*env_list;
	int		is_unset;

	env_list = test_init_env();
	is_unset = unset("TITI", env_list);
	cr_assert(get_env(env_list, "TITI") == NULL);
	cr_assert(is_unset == 0);
	free_env(&env_list);
}

Test(unset_suite, unset_malformed_name) {
	t_list	*env_list;
	int		is_unset = -1;

	env_list = test_init_env();
	is_unset = unset("TITI=", env_list);
	printf("is unset %d\n", is_unset);
	cr_assert(is_unset == 0);
	free_env(&env_list);
}
