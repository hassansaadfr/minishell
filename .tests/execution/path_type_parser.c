#include <criterion/criterion.h>
#include "minishell.h"

Test(parser_type, is_relative_path_simple)
{
	t_path type;

	type = get_path_type("./");
	cr_assert(type == RELATIVE_PATH);
}

Test(parser_type, is_relative_path_simple2)
{
	t_path type;

	type = get_path_type("./unpath");
	cr_assert(type == RELATIVE_PATH);
}

Test(parser_type, is_absolute_path)
{
	t_path type;

	type = get_path_type("/");
	cr_assert(type == ABSOLUTE_PATH);
}

Test(parser_type, is_absolute_path2)
{
	t_path type;

	type = get_path_type("/unpath");
	cr_assert(type == ABSOLUTE_PATH);
}

Test(parser_type, is_absolute_path3)
{
	t_path type;

	type = get_path_type("/empty");
	cr_assert(type == ABSOLUTE_PATH);
}
