/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Unit Tests for {echo.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(run_echo, empty_cmd, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_echo("", &sh);
    cr_assert_stdout_eq_str("\n");
}

Test(run_echo, null_cmd, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_echo(NULL, &sh);
    cr_assert_stdout_eq_str("\n");
}

Test(run_echo, legit_cmd, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_echo(" hello world", &sh);
    cr_assert_stdout_eq_str("hello world\n");
}
