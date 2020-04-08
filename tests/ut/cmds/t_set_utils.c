/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {set_utils.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(create_local_env, test)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    int ret = create_local_env(&sh.var);

    cr_assert_null(sh.var[0]);
    cr_assert_eq(ret, 0);
}

Test(show_local_env, local_env_is_null, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    int ret = create_local_env(&sh.var);

    write(1, "\n", 1);
    show_local_env(&sh);
    cr_assert_stdout_eq_str("\n");
}

Test(show_local_env, local_env_is_ok, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    int ret = create_local_env(&sh.var);

    run_set(" a b", &sh);
    run_set(" c d", &sh);
    run_set(" e f", &sh);
    write(1, "\n", 1);
    show_local_env(&sh);
    cr_assert_stdout_eq_str("\na\tb\nc\td\ne\tf");
}

Test(show_local_env, local_env_need_sort, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    int ret = create_local_env(&sh.var);

    run_set(" e f", &sh);
    run_set(" a b", &sh);
    run_set(" c d", &sh);
    write(1, "\n", 1);
    show_local_env(&sh);
    cr_assert_stdout_eq_str("\na\tb\nc\td\ne\tf");
}
