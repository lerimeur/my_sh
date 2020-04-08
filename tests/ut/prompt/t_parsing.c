/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {parsing.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "prompt.h"

Test(is_printable, no_1)
{
    cr_assert_eq(is_printable('!'), 1);
}

Test(is_printable, no_5)
{
    cr_assert_eq(is_printable('~'), 1);
}

Test(is_printable, no_6)
{
    cr_assert_eq(is_printable(127), 0);
}

Test(is_printable, no_2)
{
    cr_assert_eq(is_printable(' '), 1);
}

Test(is_printable, no_3)
{
    cr_assert_eq(is_printable(9), 0);
}

Test(is_printable, no_4)
{
    cr_assert_eq(is_printable(26), 0);
}

Test(my_realloc, size_is_same)
{
    char *src = strdup("hello world!");
    char *exp = strdup("hello world!");
    char *res = my_realloc(src, 0);

    cr_assert_str_eq(res, exp);
}

Test(my_realloc, add)
{
    char *src = strdup("hello world!");
    char *exp = strdup("hello world!");
    char *res = my_realloc(src, 12);

    cr_assert_str_eq(res, exp);
}
