/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {history.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

void print_history(char **env);
FILE *set_up_file(char **env);

extern char **environ;

Test(run_history, test, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};

    run_history("", &sh);
}

Test(print_history, test, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};

    print_history(sh.env);
}

Test(run_history_search, test, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};

    run_history_seach("!ls", &sh);
}

Test(set_up_file, test)
{
    cr_assert_not_null(set_up_file(NULL));
}
