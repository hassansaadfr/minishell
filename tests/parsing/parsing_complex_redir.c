#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

void	exp_type_and_arg(t_token *token, int type, char *arg)
{
	cr_expect(token->type == type, "type = %d", token->type);
	cr_expect(strcmp(token->arg, arg) == 0, "\targ = \"%10.10s\"\n", token->arg); 
}

Test(parsing_complex_redir_suite, complex_redir_1)
{
	char    *line = NULL;
	t_list  *list = NULL;
	t_token *token = NULL;
	int     i = 0;

	line = "cmd1 > file1>> file2<file3";
	list = parsing(line);
	while (list)
	{   
		token = list->content;
		if (i == 0)
			exp_type_and_arg(token, ARG, "cmd1");
		else if (i == 1)
			exp_type_and_arg(token, REDIR_SUP, ">");
		else if (i == 2)
			exp_type_and_arg(token, FD, "file1");
		else if (i == 3)
			exp_type_and_arg(token, REDIR_DSUP, ">>");
		else if (i == 4)
			exp_type_and_arg(token, FD, "file2");
		else if (i == 5)
			exp_type_and_arg(token, REDIR_INF, "<");
		else if (i == 6)
			exp_type_and_arg(token, FD, "file3");
		list = list->next;
		i++;
	}   
	cr_expect(i == 7); 
}

Test(parsing_complex_redir_suite, complex_redir_2)
{
	char    *line = NULL;
	t_list  *list = NULL;
	t_token *token = NULL;
	int     i = 0;

	line = "cmd1 > file1>> file2<file3 arg1 arg2";
	list = parsing(line);
	while (list)
	{   
		token = list->content;
		if (i == 0)
			exp_type_and_arg(token, ARG, "cmd1");
		else if (i == 1)
			exp_type_and_arg(token, REDIR_SUP, ">");
		else if (i == 2)
			exp_type_and_arg(token, FD, "file1");
		else if (i == 3)
			exp_type_and_arg(token, REDIR_DSUP, ">>");
		else if (i == 4)
			exp_type_and_arg(token, FD, "file2");
		else if (i == 5)
			exp_type_and_arg(token, REDIR_INF, "<");
		else if (i == 6)
			exp_type_and_arg(token, FD, "file3");
		else if (i == 7)
			exp_type_and_arg(token, ARG, "arg1");
		else if (i == 8)
			exp_type_and_arg(token, ARG, "arg2");
		list = list->next;
		i++;
	}   
	cr_expect(i == 9); 
}

Test(parsing_complex_redir_suite, complex_redir_3)
{
	char    *line = NULL;
	t_list  *list = NULL;
	t_token *token = NULL;
	int     i = 0;

	line = "<file1 cmd< file2 arg1>file3 arg2 >>file4";
	list = parsing(line);
	while (list)
	{   
		token = list->content;
		if (i == 0)
			exp_type_and_arg(token, REDIR_INF, "<");
		else if (i == 1)
			exp_type_and_arg(token, FD, "file1");
		else if (i == 2)
			exp_type_and_arg(token, ARG, "cmd");
		else if (i == 3)
			exp_type_and_arg(token, REDIR_INF, "<");
		else if (i == 4)
			exp_type_and_arg(token, FD, "file2");
		else if (i == 5)
			exp_type_and_arg(token, ARG, "arg1");
		else if (i == 6)
			exp_type_and_arg(token, REDIR_SUP, ">");
		else if (i == 7)
			exp_type_and_arg(token, FD, "file3");
		else if (i == 8)
			exp_type_and_arg(token, ARG, "arg2");
		else if (i == 9)
			exp_type_and_arg(token, REDIR_DSUP, ">>");
		else if (i == 10)
			exp_type_and_arg(token, FD, "file4");
		list = list->next;
		i++;
	}   
	cr_expect(i == 11); 
}
