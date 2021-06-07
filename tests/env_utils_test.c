#include <criterion/criterion.h>
#include "minishell.h"
#include <fcntl.h>

static char		*concat_name_value_env(t_list *list)
{
	char	*name;
	char	*value;
	char	*out;

	name = ((t_env *)list->content)->name;
	value = ((t_env *)list->content)->value;
	out = ft_strjoin(name, "=");
	out = ft_strjoin(out, value);
	return (out);
}

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

Test(init_env_suite, init_env_basic)
{
	char	**env;
	char	*full_env;
	t_list	*env_list;
	int		arr_size;
	int		i;

	env = init_dummy_arrstr();
	i = 0;
	arr_size = get_strarr_size(env);
	env_list = init_env(env);
	while (i < arr_size)
	{
		full_env = concat_name_value_env(env_list);
		if ((ft_strncmp(full_env, env[i], ft_strlen(env[i]))) == 0)
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

Test(init_env_suite, init_env_empty)
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

Test(get_env_suite, get_env_exist)
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
		returned = concat_name_value_env(tmp);
	diff = ft_strncmp(expected, returned, ft_strlen(expected) + 1);
	if (diff != 0)
		printf("++++++\nExpected: %s\nReturned: %s\n++++++\n", expected, returned);
	free_env(&env_list);
	cr_assert(diff == 0);
}

Test(get_env_suite, get_env_invalid_name)
{
	t_list	*env_list;
	t_list	*tmp;

	env_list = test_init_env();
	tmp = get_env(env_list, ft_strdup("="));
	cr_assert(tmp == NULL);
	free_env(&env_list);
}

Test(get_env_suite, get_env_undefined)
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

Test(get_env_suite, get_env_exist_malformed)
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

Test(get_env_suite, get_env_exist_malformed2)
{
	t_list	*env_list;
	t_list	*tmp;

	env_list = test_init_env();
	tmp = get_env(env_list, ft_strdup("FOO="));
	cr_assert(tmp != NULL);
	free_env(&env_list);
}

Test(get_env_suite, get_env_NULL)
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

Test(delete_env_suite, delete_exist)
{
	t_list	*env_list;
	t_list	*tmp;
	int		expected;
	int		returned;

	expected = 1;
	returned = -1;
	env_list = test_init_env();
	returned = delete_env(env_list, "KIND");
	tmp = get_env(env_list, "KIND");
	cr_expect(tmp == NULL);
	free_env(&env_list);
	cr_assert(expected == returned, "delete_exist returned %d expected %d\n", returned, expected);
}

Test(delete_env_suite, delete_undefined)
{
	t_list	*env_list;
	int		expected;
	int		returned;

	expected = 0;
	returned = -1;
	env_list = test_init_env();
	returned = delete_env(env_list, "UNDEFINED");
	free_env(&env_list);
	cr_assert(expected == returned, "delete_exist returned %d expected %d\n", returned, expected);
}

Test(delete_env_suite, delete_null)
{
	t_list	*env_list;
	int		expected;
	int		returned;

	expected = 0;
	returned = -1;
	env_list = test_init_env();
	returned = delete_env(env_list, NULL);
	free_env(&env_list);
	cr_assert(expected == returned, "delete_exist returned %d expected %d\n", returned, expected);
}

Test(delete_env_suite, delete_invalid_name)
{
	t_list	*env_list;
	int		expected;
	int		returned;

	expected = 0;
	returned = -1;
	env_list = test_init_env();
	returned = delete_env(env_list, ft_strdup("FOO="));
	free_env(&env_list);
	cr_assert(expected == returned, "expected %d returned %d\n", expected, returned);
}

Test(delete_env_suite, delete_malformed)
{
	t_list	*env_list;
	int		expected;
	int		returned;

	expected = 0;
	returned = -1;
	env_list = test_init_env();
	returned = delete_env(env_list, ft_strdup("FOO="));
	free_env(&env_list);
	cr_assert(expected == returned);
}

Test(new_env_suite, new_valid)
{
	t_list	*env_list;
	t_list	*tmp;
	char	*new_env_value;
	char	*expected;
	int		created;
	int		diff;
	int		size;

	diff = -1;
	new_env_value = ft_strdup("NEW=NEWONE");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	created = new_env(env_list, new_env_value);
	cr_assert(created == 1);
	tmp = get_env(env_list, "NEW");
	cr_assert(tmp != NULL);
	expected = concat_name_value_env(tmp);
	diff = ft_strncmp(expected, new_env_value, ft_strlen(new_env_value) + 1);
	if (size + 1 == ft_lstsize(env_list))
	cr_assert(size + 1 == ft_lstsize(env_list));
	free_env(&env_list);
	cr_assert(diff == 0);
}

Test(new_env_suite, new_valid_tricky)
{
	t_list	*env_list;
	t_list	*tmp;
	char	*new_env_value;
	char	*full_env;
	int		created;
	int		diff;
	int		size;

	diff = -1;
	new_env_value = ft_strdup("NEW=NEWONE=ERROR");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	created = new_env(env_list, new_env_value);
	cr_assert(created == 1);
	tmp = get_env(env_list, "NEW");
	cr_assert(tmp != NULL);
	full_env = concat_name_value_env(tmp);
	diff = ft_strncmp(full_env, new_env_value, ft_strlen(new_env_value) + 1);
	if (size + 1 == ft_lstsize(env_list))
	cr_assert(size + 1 == ft_lstsize(env_list));
	free_env(&env_list);
	free(full_env);
	cr_assert(diff == 0);
}

Test(new_env_suite, new_already_exist)
{
	t_list	*env_list;
	char	*new_env_value;
	int		created;
	int		size;

	new_env_value = ft_strdup("FOO=FOOTU");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	created = new_env(env_list, new_env_value);
	cr_assert(created == 0);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
//	free(new_env_value);
}

Test(new_env_suite, new_empty_value)
{
	t_list	*env_list;
	char	*new_env_value;
	int		created;
	int		size;

	new_env_value = ft_strdup("FOO=");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	created = new_env(env_list, new_env_value);
	cr_assert(created == 0, "Expected: %d | Return %d\n", 0, created);
	cr_assert(size == ft_lstsize(env_list), "Expected: %d | Return %d\n", ft_lstsize(env_list), size);
	free_env(&env_list);
	free(new_env_value);
}

Test(new_env_suite, new_null)
{
	t_list	*env_list;
	char	*new_env_value;
	int		created;
	int		size;

	new_env_value = NULL;
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	created = new_env(env_list, new_env_value);
	cr_assert(created == 0, "Expected: %d | Return %d\n", 0, created);
	cr_assert(size == ft_lstsize(env_list), "Expected: %d | Return %d\n", ft_lstsize(env_list), size);
	free_env(&env_list);
	free(new_env_value);
}

Test(edit_env_suite, edit_basic)
{
	t_list	*env_list;
	t_list	*tmp;
	char	*new_env_value;
	char	*full_value;
	int		edited;
	int		size;
	int		diff;

	new_env_value = ft_strdup("FOO=BRUUUUUH");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	tmp = get_env(env_list, "FOO");
	cr_assert(tmp != NULL);
	full_value = concat_name_value_env(tmp);
	diff = ft_strncmp(full_value, new_env_value, ft_strlen(new_env_value) + 1);
	cr_assert(diff == 0);
	free(full_value);
	free_env(&env_list);
//	free(new_env_value);
}

Test(edit_env_suite, edit_tricky)
{
	t_list	*env_list;
	t_list	*tmp;
	char	*new_env_value;
	char	*full_env;
	int		edited;
	int		size;
	int		diff;

	new_env_value = ft_strdup("FOO=BRUUUUUH=BRAHHHHH");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	full_env = concat_name_value_env(get_env(env_list, "FOO"));
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	tmp = get_env(env_list, "FOO");
	cr_assert(tmp != NULL);
	diff = ft_strncmp(full_env, new_env_value, ft_strlen(new_env_value) + 1);
	cr_assert(diff == 0);
	free_env(&env_list);
//	free(new_env_value);
}

Test(edit_env_suite, edit_tricky_bis)
{
	t_list	*env_list;
	t_list	*tmp;
	char	*new_env_value;
	char	*full_env;
	int		edited;
	int		size;
	int		diff;

	new_env_value = ft_strdup("FOO=BRUUUUUH=BRAHHHHH=BROOOOOOOOOOH");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	full_env = concat_name_value_env(get_env(env_list, "FOO"));
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	tmp = get_env(env_list, "FOO");
	cr_assert(tmp != NULL);
	diff = ft_strncmp(full_env, new_env_value, ft_strlen(new_env_value) + 1);
	cr_assert(diff == 0);
	free_env(&env_list);
//	free(new_env_value);
}

Test(edit_env_suite, edit_undefined)
{
	t_list	*env_list;
	char	*new_env_value;
	int		edited;
	int		size;

	new_env_value = ft_strdup("UNDEFINED=BRUUUUUH");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	cr_assert(edited == 0);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
	free(new_env_value);
}

Test(edit_env_suite, edit_null)
{
	t_list	*env_list;
	char	*new_env_value;
	int		edited;
	int		size;

	new_env_value = NULL;
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	cr_assert(edited == 0);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
}

Test(edit_env_suite, edit_empty_value)
{
	t_list	*env_list;
	t_list	*tmp;
	char	*new_env_value;
	char	*full_env;
	int		edited;
	int		size;
	int		diff;

	new_env_value = ft_strdup("FOO=");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	full_env = concat_name_value_env(get_env(env_list, "FOO"));
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	tmp = get_env(env_list, "FOO");
	cr_assert(tmp != NULL);
	diff = ft_strncmp(full_env, new_env_value, ft_strlen(new_env_value) + 1);
	cr_assert(diff == 0);
	free_env(&env_list);
//	free(new_env_value);
}

Test(edit_env_suite, edit_no_separator)
{
	t_list	*env_list;
	char	*new_env_value;
	int		edited;
	int		size;

	new_env_value = ft_strdup("FOO");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
	free(new_env_value);
}

Test(edit_env_suite, edit_no_name)
{
	t_list	*env_list;
	char	*new_env_value;
	int		edited;
	int		size;

	new_env_value = ft_strdup("=FOO");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	cr_assert(edited == 0);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
	free(new_env_value);
}

Test(edit_env_suite, edit_value_should_be_null)
{
	t_list	*env_list;
	char	*new_env_value;
	int		edited;
	int		size;
	t_env	*t;

	new_env_value = ft_strdup("FOO");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	t = get_env(env_list, "FOO")->content;
	cr_assert(t->value == NULL);
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
	free(new_env_value);
}

Test(edit_env_suite, edit_value_should_be_empty)
{
	t_list	*env_list;
	char	*new_env_value;
	int		edited;
	int		size;
	t_env	*t;

	new_env_value = ft_strdup("FOO=");
	env_list = test_init_env();
	size = ft_lstsize(env_list);
	edited = edit_env(env_list, new_env_value);
	t = get_env(env_list, "FOO")->content;
	cr_assert(t->value != NULL);
	cr_assert(ft_strlen(t->value) == 0);
	cr_assert(edited == 1);
	cr_assert(size == ft_lstsize(env_list));
	free_env(&env_list);
	free(new_env_value);
}
