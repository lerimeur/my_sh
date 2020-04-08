/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for load_alias.c
*/

#include "unit_tests.h"
#include "mysh.h"

Test(split_line, legit_line)
{
    char **line = split_line(strdup(".. cd .."));

    cr_assert_str_eq(line[0], "..");
    cr_assert_str_eq(line[1], "cd ..");
    cr_assert_null(line[2]);
}

Test(split_line, complex_line)
{
    char **line = split_line(strdup("lul cd ..;;; ezz pezoeojzoezezeza ze l"));

    cr_assert_str_eq(line[0], "lul");
    cr_assert_str_eq(line[1], "cd ..;;; ezz pezoeojzoezezeza ze l");
    cr_assert_null(line[2]);
}

Test(split_line, invalid_line)
{
    char **line = split_line(strdup(".."));

    cr_assert_str_eq(line[0], "..");
    cr_assert_str_eq(line[1], "");
    cr_assert_null(line[2]);
}
