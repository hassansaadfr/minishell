#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

static char		**init_dummy_arrstr(void)
{
	char	**out;
	char	*word1 = "NAME=MINISHELL";
	char	*word2 = "KIND=SHELL";
	char	*word3 = "FOO=BAR";

	out = malloc(sizeof(char*) * (3 + 1));
	out[0] = ft_strdup(word1);
	out[1] = ft_strdup(word2);
	out[2] = ft_strdup(word3);
	out[3] = NULL;
	return (out);
}

Test(init_env, init_env_basic)
{
	char	**env;
	t_list	*env_list;
	int		arr_size;
	int		i;

	env = init_dummy_arrstr();
	i = 0;
	arr_size = get_strarr_size(env);
	env_list = init_env(env);
	while (i < arr_size)
	{
		if ((ft_strncmp(env_list->content, env[i], ft_strlen(env[i]) + 1)) == 0)
			env_list = env_list->next;
		else
		{
			free_env(&env_list);
			free_split(env);
			cr_assert(0);
		}
		i++;
	}
	free_env(&env_list);
	free_split(env);
	cr_assert(1);
}

Test(init_env, init_env_empty)
{
	char	**env;
	t_list	*env_list;

	env = NULL;
	env_list = init_env(env);
	free_env(&env_list);
	cr_assert(env_list == NULL);
}

static t_list	*test_init_env(void)
{
	t_list	*env_list;
	char	**env;

	env = init_dummy_arrstr();
	env_list = init_env(env);
	return (env_list);
}

Test(get_env, get_env_exist)
{
	t_list	*env_list;
	char	*returned;
	t_list	*tmp;
	char	*expected;
	int		diff;

	expected = "FOO=BAR";
	returned = NULL;
	env_list = test_init_env();
	tmp = get_env(env_list, "FOO");
	if (tmp)
		returned = tmp->content;
	diff = ft_strncmp(expected, returned, ft_strlen(expected) + 1);
	if (diff != 0)
		printf("++++++\nExpected: %s\nReturned: %s\n++++++\n", expected, returned);
	free_env(&env_list);
	cr_assert(diff == 0);
}

Test(get_env, get_env_undefined)
{
	t_list	*env_list;
	char	*returned;
	t_list	*tmp;
	char	*expected;

	expected = NULL;
	returned = NULL;
	env_list = test_init_env();
	tmp = get_env(env_list, "UNDEFINED");
	if (tmp)
		returned = tmp->content;
	free_env(&env_list);
	cr_assert(expected == returned);
}

Test(get_env, get_env_exist_malformed)
{
	t_list	*env_list;
	char	*returned;
	t_list	*tmp;
	char	*expected;

	expected = NULL;
	returned = NULL;
	env_list = test_init_env();
	tmp = get_env(env_list, "FO");
	if (tmp)
		returned = tmp->content;
	free_env(&env_list);
	cr_assert(expected == returned);
}

Test(get_env, get_env_exist_malformed2)
{
	t_list	*env_list;
	char	*returned;
	t_list	*tmp;
	char	*expected;

	expected = NULL;
	returned = NULL;
	env_list = test_init_env();
	tmp = get_env(env_list, "FOO=");
	if (tmp)
		returned = tmp->content;
	free_env(&env_list);
	cr_assert(expected == returned);
}

Test(get_env, get_env_NULL)
{
	t_list	*env_list;
	char	*returned;
	t_list	*tmp;
	char	*expected;

	expected = NULL;
	returned = NULL;
	env_list = test_init_env();
	tmp = get_env(env_list, NULL);
	if (tmp)
		returned = tmp->content;
	free_env(&env_list);
	cr_assert(expected == returned);
}
