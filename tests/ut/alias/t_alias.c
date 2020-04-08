/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit tests for alias.c
*/

#include "unit_tests.h"
#include "mysh.h"

Test(get_nb_line, valid_file)
{
    int nb_line = get_nb_line("./tests/ut/.t_42shrc");

    cr_assert_eq(nb_line, 4);
}

Test(get_nb_line, invalid_file)
{
    int nb_line = get_nb_line(".lol");

    cr_assert_eq(nb_line, -1);
}

Test(get_nb_line, invalid_file_2)
{
    int nb_line = get_nb_line("./tests/ut/.t_42shrc_f");

    cr_assert_eq(nb_line, -1);
}

Test(load_alias, invalid_file)
{
    char ***res = load_alias(4, ".lol");

    cr_assert_null(res);
}

Test(load_alias, invalid_nb_line)
{
    char ***res = load_alias(0, "./tests/ut/.t_42shrc");

    cr_assert_null(res);
}

Test(load_alias, valid)
{
    char ***res = load_alias(get_nb_line("./tests/ut/.t_42shrc") + 1,
    "./tests/ut/.t_42shrc");

    cr_assert_str_eq(res[0][0], "ll");
    cr_assert_str_eq(res[0][1], "ls -la");
    cr_assert_str_eq(res[1][0], "re");
    cr_assert_str_eq(res[1][1], "make re");
    cr_assert_str_eq(res[2][0], "va");
    cr_assert_str_eq(res[2][1], "valgrind");
    cr_assert_str_eq(res[3][0], "..");
    cr_assert_str_eq(res[3][1], "cd ..");
}
