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

Test(parsing_negatives_suite, echo_dq_escDUSER_DUSER_dq)
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

Test(parsing_negatives_suite, echo_bsDbsUdqSERsq)
{
    char    line[]= "echo \\$\\U\"SER\"";
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
	char	neg_str[] = "$USER";

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


Test(parsing_negatives_suite, ls_smc_ls_Esmc_smc_ls_smc)
{
    char    line[]= "ls ; ls \\; ; ls \";\" ; ls ';' ;";
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
            cr_expect(strcmp(token->arg, "ls") == 0);
        }
        if (i == 1)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "ls") == 0);
        }
        if (i == 3)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, neg_str) == 0);
        }
        if (i == 4)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
        }
        if (i == 5)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "ls") == 0);
        }
        if (i == 6)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, neg_str) == 0);
        }
        if (i == 7)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
        }
		if (i == 8)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "ls") == 0);
        }
        if (i == 9)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, neg_str) == 0);
        }
        if (i == 10)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
        }
        list = list->next;
        i++;
    }
    cr_expect(i == 11);
}

Test(parsing_negatives_suite, smc_ls_Esmc_smc_ls_smc_NO_SPACE)
{
    char    line[]= "\\;;\";;;;;\";';';";
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;
	char	neg_str1[] = ";";
	char	neg_str2[] = ";;;;;";

	neg_str1[0] = -neg_str1[0];
	neg_str2[0] = -neg_str2[0];
	neg_str2[1] = -neg_str2[1];
	neg_str2[2] = -neg_str2[2];
	neg_str2[3] = -neg_str2[3];
	neg_str2[4] = -neg_str2[4];
	
    list = parsing(line);
    while (list)
    {
        token = list->content;
        if (i == 0)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, neg_str1) == 0);
        }
        if (i == 1)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
		}
	    if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, neg_str2) == 0);
        }
        if (i == 3)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
		}
		if (i == 4)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, neg_str1) == 0);
        }
        if (i == 5)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0);
		}
        list = list->next;
        i++;
    }
    cr_expect(i == 6);
}
