#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_basic_suite, echo_arg1)
{
	char	*line = NULL;
	t_list	*list = NULL;
	t_token *token = NULL;
	int		i = 0;

	line = "echo arg1";
	list = parsing(line);
	while (list)
	{
		token = list->content;
		if (i == 0)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "echo") == 0);
		}
		if (i == 1)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg1") == 0);
		}
		list = list->next;
		i++;
	}
	cr_expect(i == 2);
}

Test(parsing_basic_suite, echo_arg1_arg2_smc)
{
	char	*line = NULL;
	t_list	*list = NULL;
	t_token *token = NULL;
	int		i = 0;

	line = "echo arg1 arg2 ;";
	list = parsing(line);
	while (list)
	{
		token = list->content;
		if (i == 0)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "echo") == 0);
		}
		if (i == 1)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg1") == 0);
		}
		if (i == 2)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg2") == 0);
		}
		if (i == 3)
		{
			cr_expect(token->type == S_COLON);
			cr_expect(strcmp(token->arg, ";") == 0);
		}
		list = list->next;
		i++;
	}
	cr_expect(i == 4);
}

Test(parsing_basic_suite, echo_arg1_arg2_smc_echo2_arg1_arg2)
{
	char	*line = NULL;
	t_list	*list = NULL;
	t_token *token = NULL;
	int		i = 0;

	line = "echo arg1 arg2 ; echo2 arg1 arg2";
	list = parsing(line);
	while (list)
	{
		token = list->content;
		if (i == 0)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "echo") == 0);
		}
		if (i == 1)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg1") == 0);
		}
		if (i == 2)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg2") == 0);
		}
		if (i == 3)
		{
			cr_expect(token->type == S_COLON);
			cr_expect(strcmp(token->arg, ";") == 0);
		}
		if (i == 4)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "echo2") == 0);
		}
		if (i == 5)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg1") == 0);
		}
		if (i == 6)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "arg2") == 0);
		}
		list = list->next;
		i++;
	}
	cr_expect(i == 7);
}
