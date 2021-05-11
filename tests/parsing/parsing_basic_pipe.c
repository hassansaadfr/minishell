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

void    exp_type_and_arg_plus_line(t_token *token, int type, char *arg, int line)
{
    cr_expect(token->type == type, "LINE:%3d\ttype = %d\n", line, token->type);
    cr_expect(strcmp(token->arg, arg) == 0, "LINE:%3d --\targ = \"%10.10s\"\n", line, token->arg);
}

Test(parsing_basic_pipe_suite, complex_pipe_1)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "<file cmd1|cmd2";
    list = parsing(line);
    while (list)
    {   
        token = list->content;
        if (i == 0)
			exp_type_and_arg_plus_line(token, REDIR_INF, "<", __LINE__);
		else if (i == 1)
			exp_type_and_arg_plus_line(token, FD, "file", __LINE__);
		else if (i == 2)
			exp_type_and_arg_plus_line(token, ARG, "cmd1", __LINE__);
		else if (i == 3)
			exp_type_and_arg_plus_line(token, PIPE, "|", __LINE__);
		else if (i == 4)
			exp_type_and_arg_plus_line(token, ARG, "cmd2", __LINE__);
        list = list->next;
        i++;
    }   
    cr_expect(i == 5); 
}

Test(parsing_basic_pipe_suite, complex_pipe_2)
{
    char    *line = NULL;
    t_list  *list = NULL;
    t_token *token = NULL;
    int     i = 0;

    line = "<file cmd1|>>file cmd2 arg1";
    list = parsing(line);
    while (list)
    {   
        token = list->content;
        if (i == 0)
			exp_type_and_arg_plus_line(token, REDIR_INF, "<", __LINE__);
		else if (i == 1)
			exp_type_and_arg_plus_line(token, FD, "file", __LINE__);
		else if (i == 2)
			exp_type_and_arg_plus_line(token, ARG, "cmd1", __LINE__);
		else if (i == 3)
			exp_type_and_arg_plus_line(token, PIPE, "|", __LINE__);
		else if (i == 4)
			exp_type_and_arg_plus_line(token, REDIR_DSUP, ">>", __LINE__);
		else if (i == 5)
			exp_type_and_arg_plus_line(token, FD, "file", __LINE__);
		else if (i == 6)
			exp_type_and_arg_plus_line(token, ARG, "cmd2", __LINE__);
		else if (i == 7)
			exp_type_and_arg_plus_line(token, ARG, "arg1", __LINE__);
        list = list->next;
        i++;
    }   
    cr_expect(i == 8); 
}

