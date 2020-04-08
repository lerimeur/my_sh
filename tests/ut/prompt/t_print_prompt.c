/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {print_prompt.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "prompt.h"

static void free_sh(sh_t *sh)
{
    free(sh->alias);
    free(sh->env);
    free(sh->var);
    free(sh->pwd);
    free(sh->home);
    free(sh->user);
    free(sh->previous_line);
}

Test(get_sh_var, mode_invalid)
{
    cr_assert_null(get_sh_var(3, NULL));
}

Test(get_sh_var, valid)
{
    sh_t sh = {malloc(1),
    malloc(2),
    malloc(3),
    malloc(4),
    malloc(5),
    malloc(6),
    malloc(7)
    };
    sh_t *res = NULL;

    cr_assert_null(get_sh_var(1, &sh));
    res = get_sh_var(2, NULL);
    cr_assert_eq(res->alias, sh.alias);
    cr_assert_eq(res->env, sh.env);
    cr_assert_eq(res->var, sh.var);
    cr_assert_eq(res->pwd, sh.pwd);
    cr_assert_eq(res->home, sh.home);
    cr_assert_eq(res->user, sh.user);
    cr_assert_eq(res->previous_line, sh.previous_line);
    free_sh(&sh);
}

Test(inthandler, env_null, .init = redirect_all_stdout)
{
    sh_t sh = {calloc(1, sizeof(char)),
    calloc(2, sizeof(char)),
    calloc(3, sizeof(char)),
    calloc(4, sizeof(char)),
    calloc(5, sizeof(char)),
    calloc(6, sizeof(char)),
    calloc(7, sizeof(char))
    };

    cr_assert_null(get_sh_var(1, &sh));
    write(1, "\n", 1);
    inthandler(2);
    write(1, "\n", 1);
    cr_assert_stdout_eq_str("\n\033[1m\x1B[36m42SH \x1B[35m\033[1m\x1B[36m42S\
H \x1B[35m\n");
    free_sh(&sh);
}
