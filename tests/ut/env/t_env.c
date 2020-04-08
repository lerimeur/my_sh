/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit tests for {env.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(run_env, test, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = malloc(3 * sizeof(char *));
    if (sh.env == NULL)
        cr_skip_test("run env: env prep failed\n");
    sh.env[0] = strdup("hello world");
    sh.env[1] = strdup("lol");
    sh.env[2] = NULL;
    if (!sh.env[0] || !sh.env[1])
        cr_skip_test("run env: env prep failed\n");
    write(1, "\n", 1);
    run_env(NULL, &sh);
    cr_assert_stdout_eq_str("\nhello world\nlol\n");
}
