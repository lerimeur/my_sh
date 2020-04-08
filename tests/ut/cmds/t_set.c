/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {set.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

Test(run_set, param_is_empty, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_set("", &sh);
    cr_assert_stdout_eq_str("\n_\t\n\n");
}

Test(run_set, param_is_invalid, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_set(" lol-=bonjour", &sh);
    cr_assert_stdout_eq_str("\nset: Variable name must contain alphanumeric \
characters.\n");
}

Test(run_set, param_is_invalid_2, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_set(" ==bonjour", &sh);
    cr_assert_stdout_eq_str("\nset: Variable name must contain alphanumeric \
characters.\n");
}

Test(run_set, param_is_valid)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol=bonjour", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tbonjour");
}

Test(run_set, param_is_valid_2)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol", &sh);
    cr_assert_str_eq(sh.var[0], "lol\t");
}

Test(run_set, multiple_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol=bonjour lul lil hello=world", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tbonjour");
    cr_assert_str_eq(sh.var[1], "lul\t");
    cr_assert_str_eq(sh.var[2], "lil\t");
    cr_assert_str_eq(sh.var[3], "hello\tworld");
    cr_assert_null(sh.var[4]);
}

Test(run_set, change_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol=bonjour", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tbonjour");
    run_set(" lol=non", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tnon");
}

Test(run_set, multiple_call)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol=bonjour", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tbonjour");
    cr_assert_null(sh.var[1]);
    run_set(" chien=yr", &sh);
    cr_assert_str_eq(sh.var[1], "chien\tyr");
    cr_assert_null(sh.var[2]);
    run_set(" rammus=ok", &sh);
    cr_assert_str_eq(sh.var[2], "rammus\tok");
    cr_assert_null(sh.var[3]);
    run_set(" ez=game", &sh);
    cr_assert_str_eq(sh.var[3], "ez\tgame");
    cr_assert_null(sh.var[4]);
    run_set(" ez=life", &sh);
    cr_assert_str_eq(sh.var[3], "ez\tlife");
    cr_assert_null(sh.var[4]);
    run_set(" salut=cava", &sh);
    cr_assert_str_eq(sh.var[4], "salut\tcava");
    cr_assert_null(sh.var[5]);
}

Test(run_unset, param_is_empty, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_unset("", &sh);
    cr_assert_stdout_eq_str("\nunset: Too few arguments.\n");
}

Test(run_unset, param_is_null, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_unset(NULL, &sh);
    cr_assert_stdout_eq_str("\nunset: Too few arguments.\n");
}

Test(run_unset, remove_one_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol=bonjour", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tbonjour");
    run_unset(" lol", &sh);
    cr_assert_null(sh.var[0]);
}

Test(run_unset, remove_multiple_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    run_set(" lol=bonjour", &sh);
    cr_assert_str_eq(sh.var[0], "lol\tbonjour");
    cr_assert_null(sh.var[1]);
    run_set(" zae=eeza", &sh);
    cr_assert_str_eq(sh.var[1], "zae\teeza");
    cr_assert_null(sh.var[2]);
    run_set(" rr=ur", &sh);
    cr_assert_str_eq(sh.var[2], "rr\tur");
    cr_assert_null(sh.var[3]);
    run_unset(" lol rr", &sh);
    cr_assert_str_eq(sh.var[0], "zae\teeza");
    cr_assert_null(sh.var[1]);
}
