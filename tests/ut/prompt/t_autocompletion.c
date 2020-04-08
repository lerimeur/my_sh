/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Test for {autocompletion.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "prompt.h"

Test(is_filepath, yes)
{
    cr_assert_eq(is_filepath("yes/lol"), 1);
}

Test(is_filepath, no)
{
    cr_assert_eq(is_filepath("yeslol"), 0);
}

Test(file_match, yes)
{
    cr_assert_eq(file_match("bonjour monde", "bonjour"), 1);
}

Test(file_match, no)
{
    cr_assert_eq(file_match("bonjou monde", "bonjour"), 0);
}
