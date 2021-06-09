#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_err_pipes_suite, only_pipe)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "|";
    list = parsing(line);
    cr_expect(list == NULL); 
    line = " |";
    list = parsing(line);
    cr_expect(list == NULL); 
    line = "          |";
    list = parsing(line);
    cr_expect(list == NULL); 
    line = "|    ";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_pipes_suite, pipe_exclusions)
{
    char    *line = NULL;
    t_list  *list = NULL;

	line = "cmd ; |";
    list = parsing(line);
    cr_expect(list == NULL);
	line = "cmd < |";
    list = parsing(line);
    cr_expect(list == NULL);
	line = "cmd > |";
    list = parsing(line);
    cr_expect(list == NULL);
	line = "cmd >> |";
    list = parsing(line);
    cr_expect(list == NULL);
}


