#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_err_redirs_suite, only_sup)
{
	char    *line = NULL;
	t_list  *list = NULL;

	line = ">";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = " >";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "          >";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = ">    ";
	list = parsing(line);
	cr_expect(list == NULL); 
}

Test(parsing_err_redirs_suite, only_inf)
{
	char    *line = NULL;
	t_list  *list = NULL;

	line = "<";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = " <";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "          <";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "<    ";
	list = parsing(line);
	cr_expect(list == NULL); 
}

Test(parsing_err_redirs_suite, only_dsup)
{
	char    *line = NULL;
	t_list  *list = NULL;

	line = ">>";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = " >>";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "          >>";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = ">>    ";
	list = parsing(line);
	cr_expect(list == NULL); 
}

Test(parsing_err_redirs_suite, consecutive_redirs)
{
	char    *line = NULL;
	t_list  *list = NULL;

	line = "> >";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "> >>";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "> <";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "< >";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "< >>";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = "< <";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = ">> >";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = ">> >>";
	list = parsing(line);
	cr_expect(list == NULL); 
	line = ">> <";
	list = parsing(line);
	cr_expect(list == NULL); 
}
