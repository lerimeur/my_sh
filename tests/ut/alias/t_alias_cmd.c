/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit tests for alias_cmd.c
*/

#include "unit_tests.h"
#include "mysh.h"

Test(run_alias, show_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    write(1, "\n", 1);
    run_alias("", &sh);
    cr_assert_stdout_eq_str("\n..\t(cd ..)\nll\t(ls -la)\nre\t(make re)\n\
va\t(valgrind)\n");
}

Test(run_alias, param_is_null, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    write(1, "\n", 1);
    run_alias(NULL, &sh);
    cr_assert_stdout_eq_str("\n..\t(cd ..)\nll\t(ls -la)\nre\t(make re)\n\
va\t(valgrind)\n");
}

Test(run_alias, find_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    write(1, "\n", 1);
    run_alias(" ll", &sh);
    cr_assert_stdout_eq_str("\nls -la\n");
}

Test(run_alias, add_alias)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    run_alias(" lol cd -", &sh);
    cr_assert_str_eq(sh.alias[0][0], "ll");
    cr_assert_str_eq(sh.alias[0][1], "ls -la");
    cr_assert_str_eq(sh.alias[1][0], "re");
    cr_assert_str_eq(sh.alias[1][1], "make re");
    cr_assert_str_eq(sh.alias[2][0], "va");
    cr_assert_str_eq(sh.alias[2][1], "valgrind");
    cr_assert_str_eq(sh.alias[3][0], "..");
    cr_assert_str_eq(sh.alias[3][1], "cd ..");
    cr_assert_str_eq(sh.alias[4][0], "lol");
    cr_assert_str_eq(sh.alias[4][1], "cd -");
    cr_assert_null(sh.alias[5]);
}

Test(run_alias, edit_alias)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    run_alias(" ll ls -r", &sh);
    cr_assert_str_eq(sh.alias[0][0], "ll");
    cr_assert_str_eq(sh.alias[0][1], "ls -r");
}

Test(run_unalias, param_is_null, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_unalias(NULL, &sh);
    cr_assert_stdout_eq_str("\nunalias: Too few arguments.\n");
}

Test(run_unalias, no_arg, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    run_unalias("", &sh);
    cr_assert_stdout_eq_str("\nunalias: Too few arguments.\n");
}

Test(run_unalias, one_var)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    run_unalias(" ..", &sh);
    cr_assert_str_eq(sh.alias[0][0], "ll");
    cr_assert_str_eq(sh.alias[0][1], "ls -la");
    cr_assert_str_eq(sh.alias[1][0], "re");
    cr_assert_str_eq(sh.alias[1][1], "make re");
    cr_assert_str_eq(sh.alias[2][0], "va");
    cr_assert_str_eq(sh.alias[2][1], "valgrind");
    cr_assert_null(sh.alias[3]);
}

Test(run_unalias, multiple_var_including_invalid_one)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    run_unalias(" .. ll lol test re", &sh);
    cr_assert_str_eq(sh.alias[0][0], "va");
    cr_assert_str_eq(sh.alias[0][1], "valgrind");
    cr_assert_null(sh.alias[1]);
}
