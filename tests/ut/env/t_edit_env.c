/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {edit_env.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "parser.h"

extern char **environ;

Test(find_env_value, home)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *value = find_env_value("PWD", sh.env, '=');
    char *exp = getenv("PWD");

    cr_assert_str_eq(value, exp);
}

Test(find_env_value, env_null)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0};
    char *value = find_env_value("PWD", sh.env, '=');

    cr_assert_null(value);
}

Test(find_env_value, invalid_value)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *value = find_env_value("LOL", sh.env, '=');
    char *exp = getenv("LOL");

    if (!exp)
        cr_assert_null(value);
    else
        cr_assert_str_eq(value, exp);
}

Test(change_env_var, test)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};

    if (!getenv("PWD"))
        cr_skip_test();
    change_env_var(sh.env, "PWD", "lol", "=");
    cr_assert_str_eq(find_env_value("PWD", sh.env, '='), "lol");
}
