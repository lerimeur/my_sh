/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {setenv.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(run_setenv, param_empty, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    write(1, "\n", 1);
    run_setenv("", &sh);
    cr_assert_stdout_eq_str("\nhello=world\nlul=lol\n");
}

Test(run_setenv, too_many_arg, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    write(1, "\n", 1);
    run_setenv(" lol lul in", &sh);
    cr_assert_stdout_eq_str("\nsetenv: Too many arguments.\n");
}

Test(run_setenv, invalid_arg, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    write(1, "\n", 1);
    run_setenv(" _lo pu", &sh);
    cr_assert_stdout_eq_str("\nsetenv: Variable name must begin with a \
letter.\n");
}

Test(run_setenv, invalid_arg_2, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    write(1, "\n", 1);
    run_setenv(" lo- pu", &sh);
    cr_assert_stdout_eq_str("\nsetenv: Variable name must contain alphanumeric \
characters.\n");
}

Test(run_setenv, valid_arg)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    run_setenv(" lo pu", &sh);
    cr_assert_str_eq(sh.env[0], "hello=world");
    cr_assert_str_eq(sh.env[1], "lul=lol");
    cr_assert_str_eq(sh.env[2], "lo=pu");
    cr_assert_null(sh.env[3]);
}

Test(run_setenv, valid_arg_2)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    run_setenv(" lo", &sh);
    cr_assert_str_eq(sh.env[0], "hello=world");
    cr_assert_str_eq(sh.env[1], "lul=lol");
    cr_assert_str_eq(sh.env[2], "lo=");
    cr_assert_null(sh.env[3]);
}

Test(run_setenv, change_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    run_setenv(" lul ok", &sh);
    cr_assert_str_eq(sh.env[0], "hello=world");
    cr_assert_str_eq(sh.env[1], "lul=ok");
    cr_assert_null(sh.env[2]);
}

Test(run_setenv, change_var_2)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    sh.env[0] = strdup("hello=world");
    sh.env[1] = strdup("lul=lol");
    if (sh.env[0] == NULL || sh.env[1] == NULL)
        cr_skip_test("setenv: param_empty: env's setup failed\n");
    run_setenv(" lul", &sh);
    cr_assert_str_eq(sh.env[0], "hello=world");
    cr_assert_str_eq(sh.env[1], "lul=");
    cr_assert_null(sh.env[2]);
}
