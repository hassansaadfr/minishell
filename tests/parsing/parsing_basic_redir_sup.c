#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_basic_redir_sup_suite, cmd_sp_sup_sp_file)
{
	char    *line = NULL;
	t_list  *list = NULL;
	t_token *token = NULL;
	int     i = 0;

	line = "cmd1 > file";
	list = parsing(line);
	while (list)
	{   
		token = list->content;
		if (i == 0)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "cmd1") == 0); 
		}
		if (i == 1)
		{
			cr_expect(token->type == REDIR_SUP);
			cr_expect(strcmp(token->arg, ">") == 0); 
		}
		if (i == 2)
		{
			cr_expect(token->type == FD);
			cr_expect(strcmp(token->arg, "file") == 0); 
		}
		list = list->next;
		i++;
	}   
	cr_expect(i == 3); 
}

Test(parsing_basic_redir_sup_suite, cmd_sup_file)
{
	char    *line = NULL;
	t_list  *list = NULL;
	t_token *token = NULL;
	int     i = 0;

	line = "cmd1>file";
	list = parsing(line);
	while (list)
	{   
		token = list->content;
		if (i == 0)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "cmd1") == 0); 
		}
		if (i == 1)
		{
			cr_expect(token->type == REDIR_SUP);
			cr_expect(strcmp(token->arg, ">") == 0); 
		}
		if (i == 2)
		{
			cr_expect(token->type == FD);
			cr_expect(strcmp(token->arg, "file") == 0); 
		}
		list = list->next;
		i++;
	}   
	cr_expect(i == 3); 
}

Test(parsing_basic_redir_sup_suite, sup_file_cmd)
{
	char    *line = NULL;
	t_list  *list = NULL;
	t_token *token = NULL;
	int     i = 0;

	line = ">file cmd1";
	list = parsing(line);
	while (list)
	{   
		token = list->content;
		if (i == 0)
		{
			cr_expect(token->type == REDIR_SUP);
			cr_expect(strcmp(token->arg, ">") == 0); 
		}
		if (i == 1)
		{
			cr_expect(token->type == FD);
			cr_expect(strcmp(token->arg, "file") == 0); 
		}
		if (i == 2)
		{
			cr_expect(token->type == ARG);
			cr_expect(strcmp(token->arg, "cmd1") == 0); 
		}
		list = list->next;
		i++;
	}   
	cr_expect(i == 3); 
}

