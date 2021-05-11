#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"

Test(parsing_err_smc_suite, only_smc)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = ";";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_smc_suite, spc_smc)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = " ;";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_smc_suite, spc_smc_spc)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = " ; ";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_smc_suite, smc_smc)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = ";;";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_smc_suite, smc_spc_smc)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "; ;";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_smc_suite, ls_smc_spc_smc_ls)
{
    char    *line = NULL;
    t_list  *list = NULL;

    line = "ls ; ; ls";
    list = parsing(line);
    cr_expect(list == NULL); 
}

Test(parsing_err_smc_suite, smc_exclusions)
{
	char	*line = NULL;
	t_list	*list = NULL;

	line = "cmd | ; ";
	list = parsing(line);
	cr_expect(list == NULL);
}
