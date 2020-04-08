/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit tests for alias_utils.c
*/

#include "unit_tests.h"
#include "mysh.h"

Test(show_alias, no_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    write(1, "\n", 1);
    show_alias(&sh);
    cr_assert_stdout_eq_str("\n");
}

Test(show_alias, sorted_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc_sort") + 1,
    "tests/ut/.t_42shrc_sort");
    write(1, "\n", 1);
    show_alias(&sh);
    cr_assert_stdout_eq_str("\n..\t(cd ..)\nll\t(ls -la)\nre\t(make re)\n\
va\t(valgrind)\n");
}

Test(show_alias, unsorted_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc") + 1,
    "tests/ut/.t_42shrc");
    write(1, "\n", 1);
    show_alias(&sh);
    cr_assert_stdout_eq_str("\n..\t(cd ..)\nll\t(ls -la)\nre\t(make re)\n\
va\t(valgrind)\n");
}
