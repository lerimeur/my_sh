/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit tests file for edit_alias.c
*/

#include "unit_tests.h"
#include "mysh.h"

Test(find_alias_value, existing_value, .init = redirect_all_stdout)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    write(1, "\n", 1);
    find_alias_value(alias, "ll");
    cr_assert_stdout_eq_str("\nls -la");
}

Test(find_alias_value, non_existing_value, .init = redirect_all_stdout)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    write(1, "\n", 1);
    find_alias_value(alias, "lol");
    cr_assert_stdout_eq_str("\n");
}

Test(find_alias_value, non_existing_value_2, .init = redirect_all_stdout)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    write(1, "\n", 1);
    find_alias_value(alias, " ");
    cr_assert_stdout_eq_str("\n");
}

Test(find_alias_value, alias_is_null, .init = redirect_all_stdout)
{
    char ***alias = NULL;

    write(1, "\n", 1);
    find_alias_value(alias, "ll");
    cr_assert_stdout_eq_str("\n");
}

Test(is_in_alias, existing_value, .init = redirect_all_stdout)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    bool ret = is_in_alias(alias, "ll");

    cr_assert_eq(ret, true);
}

Test(is_in_alias, non_existing_value, .init = redirect_all_stdout)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    bool ret = is_in_alias(alias, "lol");

    cr_assert_eq(ret, false);
}

Test(is_in_alias, non_existing_value_2, .init = redirect_all_stdout)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    bool ret = is_in_alias(alias, "");

    cr_assert_eq(ret, false);
}

Test(is_in_alias, alias_is_null, .init = redirect_all_stdout)
{
    char ***alias = NULL;
    bool ret = is_in_alias(alias, "ll");

    cr_assert_eq(ret, false);
}

Test(change_alias_var, existing_value)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    char **new_alias = split_line(".. cd -");

    change_alias_var(alias, new_alias);
    cr_assert_str_eq(alias[0][0], "ll");
    cr_assert_str_eq(alias[0][1], "ls -la");
    cr_assert_str_eq(alias[1][0], "re");
    cr_assert_str_eq(alias[1][1], "make re");
    cr_assert_str_eq(alias[2][0], "va");
    cr_assert_str_eq(alias[2][1], "valgrind");
    cr_assert_str_eq(alias[3][0], "..");
    cr_assert_str_eq(alias[3][1], "cd -");
}

Test(change_alias_var, non_existing_value)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    char **new_alias = split_line("lol cd -");

    change_alias_var(alias, new_alias);
    cr_assert_str_eq(alias[0][0], "ll");
    cr_assert_str_eq(alias[0][1], "ls -la");
    cr_assert_str_eq(alias[1][0], "re");
    cr_assert_str_eq(alias[1][1], "make re");
    cr_assert_str_eq(alias[2][0], "va");
    cr_assert_str_eq(alias[2][1], "valgrind");
    cr_assert_str_eq(alias[3][0], "..");
    cr_assert_str_eq(alias[3][1], "cd ..");
    cr_assert_null(alias[4]);
}

Test(add_alias_var, new_var)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    char **new_alias = split_line("lol cd -");

    alias = add_alias_var(alias, new_alias);
    cr_assert_str_eq(alias[0][0], "ll");
    cr_assert_str_eq(alias[0][1], "ls -la");
    cr_assert_str_eq(alias[1][0], "re");
    cr_assert_str_eq(alias[1][1], "make re");
    cr_assert_str_eq(alias[2][0], "va");
    cr_assert_str_eq(alias[2][1], "valgrind");
    cr_assert_str_eq(alias[3][0], "..");
    cr_assert_str_eq(alias[3][1], "cd ..");
    cr_assert_str_eq(alias[4][0], "lol");
    cr_assert_str_eq(alias[4][1], "cd -");
    cr_assert_null(alias[5]);
}

Test(remove_alias, var_is_valid_and_at_the_end)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    alias = remove_alias(alias, "..");
    cr_assert_str_eq(alias[0][0], "ll");
    cr_assert_str_eq(alias[0][1], "ls -la");
    cr_assert_str_eq(alias[1][0], "re");
    cr_assert_str_eq(alias[1][1], "make re");
    cr_assert_str_eq(alias[2][0], "va");
    cr_assert_str_eq(alias[2][1], "valgrind");
    cr_assert_null(alias[3]);
}

Test(remove_alias, var_is_valid_and_somewhere)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    alias = remove_alias(alias, "re");
    cr_assert_str_eq(alias[0][0], "ll");
    cr_assert_str_eq(alias[0][1], "ls -la");
    cr_assert_str_eq(alias[1][0], "va");
    cr_assert_str_eq(alias[1][1], "valgrind");
    cr_assert_str_eq(alias[2][0], "..");
    cr_assert_str_eq(alias[2][1], "cd ..");
    cr_assert_null(alias[3]);
}

Test(remove_alias, var_is_valid_and_at_the_beginning)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    alias = remove_alias(alias, "ll");
    cr_assert_str_eq(alias[0][0], "re");
    cr_assert_str_eq(alias[0][1], "make re");
    cr_assert_str_eq(alias[1][0], "va");
    cr_assert_str_eq(alias[1][1], "valgrind");
    cr_assert_str_eq(alias[2][0], "..");
    cr_assert_str_eq(alias[2][1], "cd ..");
    cr_assert_null(alias[3]);
}

Test(remove_alias, var_is_invalid)
{
    char ***alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");

    alias = remove_alias(alias, "..");
    cr_assert_str_eq(alias[0][0], "ll");
    cr_assert_str_eq(alias[0][1], "ls -la");
    cr_assert_str_eq(alias[1][0], "re");
    cr_assert_str_eq(alias[1][1], "make re");
    cr_assert_str_eq(alias[2][0], "va");
    cr_assert_str_eq(alias[2][1], "valgrind");
    cr_assert_null(alias[3]);
}
