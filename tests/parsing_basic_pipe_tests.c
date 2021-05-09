#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_basic_pipe_suite, cmd1_sp_pipe_sp_cm2)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "cmd1 | cmd2";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 3); 
}

Test(parsing_basic_pipe_suite, cmd1_pipe_sp_cm2)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "cmd1| cmd2";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 3); 
}

Test(parsing_basic_pipe_suite, cmd1_sp_pipe_cm2)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "cmd1 |cmd2";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 3); 
}

Test(parsing_basic_pipe_suite, cmd1_pipe_cm2)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "cmd1|cmd2";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 3); 
}

Test(parsing_basic_pipe_suite, cmd1_pipe_cmd2_arg1_pipe_cmd3)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "cmd1|cmd2 arg1|cmd3";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        if (i == 3)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "arg1") == 0); 
        }
        if (i == 4)
        {
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 5)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd3") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 6); 
}

Test(parsing_basic_pipe_suite, cmd1_pipe_cmd2_arg1_pipe_cmd3_pipe_cmd4_op1_smc)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "cmd1|cmd2 arg1|cmd3    |   cmd4 op1;";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        if (i == 3)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "arg1") == 0); 
        }
        if (i == 4)
        {
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 5)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd3") == 0); 
        }
        if (i == 6)
        {
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 7)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd4") == 0); 
        }
        if (i == 8)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "op1") == 0); 
        }
		if (i == 9)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 10); 
}

Test(parsing_basic_pipe_suite, cmd1_pipe_cmd2_arg1_pipe_cmd3_pipe_cmd4_op1_smc_cmd5_pipe_cmd6_smc)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "      cmd1|cmd2 arg1|cmd3    |   cmd4 op1;cmd5 |cmd6 ;     ";
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
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 2)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd2") == 0); 
        }
        if (i == 3)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "arg1") == 0); 
        }
        if (i == 4)
        {
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 5)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd3") == 0); 
        }
        if (i == 6)
        {
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 7)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd4") == 0); 
        }
        if (i == 8)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "op1") == 0); 
        }
		if (i == 9)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0); 
        }
        if (i == 10)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd5") == 0); 
        }
        if (i == 11)
        {
            cr_expect(token->type == PIPE);
            cr_expect(strcmp(token->arg, "|") == 0); 
        }
        if (i == 12)
        {
            cr_expect(token->type == ARG);
            cr_expect(strcmp(token->arg, "cmd6") == 0); 
        }
		if (i == 13)
        {
            cr_expect(token->type == S_COLON);
            cr_expect(strcmp(token->arg, ";") == 0); 
        }
        list = list->next;
        i++;
    }   
    cr_expect(i == 14); 
}
