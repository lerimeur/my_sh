/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {find_in_files.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "history.h"

void call_cmd(char *input, sh_t *sh);

extern char **environ;

Test(find_in_files, find_number_no_history)
{
    FILE *fd = set_up_file(environ);
    char *res;

    if (!fd)
        cr_skip_test();
    cr_assert_null(find_in_files(fd, "1"));
}

Test(find_in_files, find_number_fail)
{
    FILE *fd = set_up_file(environ);
    char *res;

    if (!fd)
        cr_skip_test();
    cr_assert_null(find_in_files(fd, "40000"));
}

Test(find_in_files, find_name_no_history)
{
    FILE *fd = set_up_file(environ);
    char *res;

    if (!fd)
        cr_skip_test();
    cr_assert_null(find_in_files(fd, "set"));
}

Test(find_in_files, find_name_fail)
{
    FILE *fd = set_up_file(environ);
    char *res;

    if (!fd)
        cr_skip_test();
    cr_assert_null(find_in_files(fd, ".set"));
}
