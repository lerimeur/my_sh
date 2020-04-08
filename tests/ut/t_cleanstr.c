/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit tests for cleanstr.c
*/

#include "unit_tests.h"
#include "mysh.h"

Test(clean_str, str_with_no_change_required)
{
    char *str = strdup("ls -la");
    char *new = clean_str(&str);
    char *exp = strdup("ls -la");

    cr_assert_str_eq(new, exp);
}

Test(clean_str, too_much_space)
{
    char *str = strdup("                 ls               -la           ");
    char *new = clean_str(&str);
    char *exp = strdup("ls -la");

    cr_assert_str_eq(new, exp);
}

Test(clean_str, complexe_command_no_change)
{
    char *str = strdup("cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; \
cd - && echo “OK”");
    char *new = clean_str(&str);
    char *exp = strdup("cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; \
cd - && echo “OK”");

    cr_assert_str_eq(new, exp);
}

Test(clean_str, complexe_command_drunk_input)
{
    char *str = strdup(";;;;;;;;;;;;;;    \tcd ; </etc/hosts\t    od   -c   \
|        \t\t\t grep xx | wc \t\t>> /tmp/z -l ; cd - && echo “OK”");
    char *new = clean_str(&str);
    char *exp = strdup("cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; \
cd - && echo “OK”");

    cr_assert_str_eq(new, exp);
}

Test(clean_str, empty_string)
{
    char *str = strdup("");
    char *new = clean_str(&str);
    char *exp = strdup("");

    cr_expect_str_eq(new, exp);
}
