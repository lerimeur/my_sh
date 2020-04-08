/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {env_utilities.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(load_env, env_is_null)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    int ret = load_env(NULL, &sh);

    cr_assert_null(sh.env);
    cr_assert_null(sh.var);
    cr_assert_eq(ret, 84);
}

Test(load_env, env_is_ok)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    int ret = 0;
    char **env = malloc(3 * sizeof(char *));

    if (env == NULL)
        cr_skip_test("load_env: env creation failed\n");
    env[0] = strdup("hello=world");
    env[1] = strdup("lol=lol");
    if (env[0] == NULL || env[1] == NULL)
        cr_skip_test("load_env: env creation failed\n");
    env[2] = NULL;
    ret = load_env(env, &sh);
    cr_assert_str_eq(sh.env[0], "hello=world");
    cr_assert_str_eq(sh.env[1], "lol=lol");
    cr_assert_null(sh.env[2]);
    cr_assert_null(sh.var[0]);
    cr_assert_eq(ret, 0);
}
