#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_escaped_suite, escaped1_echo_arg1)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "\"e\"cho arg1";
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

Test(parsing_escaped_suite, escaped2_echo_arg_long)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "\"e\"\'ch\'\\o \"arg1  long\"";
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
            cr_expect(strcmp(token->arg, "arg1  long") == 0);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped3_echo_arg_long2)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "\"e\"\'ch\'\\o \"arg1\"\"  long\"";
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
            cr_expect(strcmp(token->arg, "arg1  long") == 0);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}
