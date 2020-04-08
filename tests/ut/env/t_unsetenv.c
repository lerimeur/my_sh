/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {unsetenv.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(run_unsetenv, param_null, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0};

    write(1, "\n", 1);
    run_unsetenv(NULL, &sh);
    cr_assert_stdout_eq_str("\nunsetenv: Too few arguments.\n");
    cr_assert_eq(sh.ex, 1);
}

Test(run_unsetenv, param_empty, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0};

    write(1, "\n", 1);
    run_unsetenv("", &sh);
    cr_assert_stdout_eq_str("\nunsetenv: Too few arguments.\n");
    cr_assert_eq(sh.ex, 1);
}

Test(run_unsetenv, param_is_ok)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 10};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("unsetenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("unsetenv: param_empty: env's setup failed\n");
    run_unsetenv(" lul", &sh);
    cr_assert_str_eq(sh.env[0], "hello=world");
    cr_assert_null(sh.env[1]);
    cr_assert_eq(sh.ex, 0);
}

Test(run_unsetenv, multiple_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 10};

    sh.env = malloc(6 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("unsetenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    sh.env[2] = strdup("a=b");
    sh.env[3] = strdup("c=d");
    sh.env[4] = strdup("e=f");
    if (sh.env[0] == NULL || sh.env[1] == NULL || sh.env[2] == NULL ||
        sh.env[3] == NULL || sh.env[4] == NULL)
        cr_skip_test("unsetenv: param_empty: env's setup failed\n");
    run_unsetenv(" hello c e", &sh);
    cr_assert_str_eq(sh.env[0], "lul=lol");
    cr_assert_str_eq(sh.env[1], "a=b");
    cr_assert_null(sh.env[2]);
    cr_assert_eq(sh.ex, 0);
}
