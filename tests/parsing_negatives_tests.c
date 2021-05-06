#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_negatives_suite, echo_arg1_esc_smc)
{
    char    line[]= "echo arg1 ';'";
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
	char	neg_str[] = ";";

	neg_str[0] = -neg_str[0];
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
            cr_expect(ft_strncmp(token->arg, neg_str, 1) == 0);
		}
        list = list->next;
        i++;
    }
    cr_expect(i == 3);
}

Test(parsing_negatives_suite, echo_dq_escDuser_Duser_dq)
{
    char    line[]= "echo \"\\$USER $USER\"";
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
	char	neg_str[] = "$USER $USER";

	neg_str[0] = -neg_str[0];
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
            cr_expect(strcmp(token->arg, neg_str) == 0);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 2);
}
