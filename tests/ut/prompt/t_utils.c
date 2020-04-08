/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {utils.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "prompt.h"

Test(my_revstr, test)
{
    char *src = strdup("hello world");
    char *exp = strdup("dlrow olleh");
    char *res = NULL;

    if (!src || !exp)
        cr_skip_test();
    res = my_revstr(src);
    cr_assert_str_eq(res, exp);
}

Test(line_is_empty, no)
{
    char *line = strdup("hello world");

    cr_assert_eq(line_is_empty(line), 0);
}

Test(line_is_empty, yes)
{
    char *line = strdup("\n");

    cr_assert_eq(line_is_empty(line), 1);
}
