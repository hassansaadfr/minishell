#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_escaped_suite, echo_unclosed_sq)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "echo \'";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_escaped_suite, echo_unclosed_dq)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "echo \"";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_escaped_suite, echo_unclosed_backslash)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "echo \\";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_escaped_suite, echo_unclosed_backslah_sq)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "echo \'debut d\\\'arg\'";
    list = parsing(line);
    cr_expect(list == NULL); 
}

