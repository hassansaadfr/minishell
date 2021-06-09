#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

void	esc_str_to_neg_str(char **str_addr)
{
	int		i = 0;
	
	while ((*str_addr)[i])
	{
		
	}
}

Test(parsing_escaped_suite, escaped1_echo_arg1)
{
    char 	line[] = "\"e\"cho arg1";
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

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

Test(parsing_escaped_suite, escaped4)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "ls bon\" jour\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "ls") == 0);
        }
        if (i == 1)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "bon jour") == 0);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped5)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "ls bon jour";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "ls") == 0);
        }
        if (i == 1)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "bon") == 0);
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "jour") == 0);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 3);
}

Test(parsing_escaped_suite, escaped6)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "ls bon \"jou r\"\'je suis un test\'";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "ls";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "bon";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 2)
        {
            expected = "jou rje suis un test";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 3);
}

Test(parsing_escaped_suite, escaped7)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "ls   bon      \" jour\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "ls";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "bon";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 2)
        {
            expected = " jour";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 3);
}

Test(parsing_escaped_suite, escaped8)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "ls ma\\ \"je\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "ls";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "ma je";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped9)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo bon\" jour\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "bon jour";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped10)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"coment ca va \' toto \'\\n\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "coment ca va \' toto \'\\n";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped11)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \" \'\\ \' \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \'\\ \' ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped12)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\ \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\ ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped13)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\i \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\i ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}

Test(parsing_escaped_suite, escaped14)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\\\\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped15)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\'\\\'\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\'\\\'";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped16)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\'\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\'";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped17)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\' \\\"\'\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\' \"\'";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped18)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo   bon \" jour\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "bon";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 2)
        {
            expected = " jour";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 3, "++++++\nexpected\t%d\nreturned\t%d\n", 3, i);
}

Test(parsing_escaped_suite, escaped19)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \" \'\\\'\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \'\\\'";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped20)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \" \'\\\"\'\"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \'\"\'";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped21)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \' \"\\\" \'";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \"\\\" ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped22)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \' \"\\\"\" \\\' \'\\n\'"; // echo ' "\"" \' '\n'
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \"\\\"\" \\";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 2)
        {
            expected = "\\n";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 3, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped23)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \' \\\\\' \'\\n\'";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \\\\";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 2)
        {
            expected = "\\n";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 3, "++++++\nexpected\t%d\nreturned\t%d\n", 3, i);
}

Test(parsing_escaped_suite, escaped24)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \' \\\\\'";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = " \\\\";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped25)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\\\\\ \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\\\ ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped26)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\\\\\\\\\\\\\\\\\ ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped27)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\\\\\\\\\\\\\\\\\ ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped28)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\\\\\\\ \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\\\ ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped29)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "echo \"\\\\\\\\\\\\ \"";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "\\\\\\ ";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}

Test(parsing_escaped_suite, escaped30)
{
    char    *line = NULL;
    char    *expected = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
    int     diff = -1;

    line = "\\e\\c\\h\\o \\b\\o\\n\\j\\o\\u\\r";
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            expected = "echo";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        if (i == 1)
        {
            expected = "bonjour";
            diff = strcmp(token->arg, expected) == 0;
            cr_expect(token->type == ARG);
            cr_expect(diff, "++++++\nexpected\t%s\nreturned\t%s\n", expected, token->arg);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2, "++++++\nexpected\t%d\nreturned\t%d\n", 2, i);
}
