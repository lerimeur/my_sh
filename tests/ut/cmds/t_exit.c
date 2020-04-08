/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {exit.c}.
*/

#include "unit_tests.h"
#include "mysh.h"

int check_end_shell(char *line, int ac, int ex);

Test(run_exit, exit_empty)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8};
    pid_t child = fork();
    int wstatus = 0;

    if (child == -1)
        cr_skip_test();
    if (child == 0) {
        run_exit("", &sh);
    } else
        waitpid(child, &wstatus, 0);
    if (WIFEXITED(wstatus))
        cr_assert_eq(WEXITSTATUS(wstatus), 8);
    else
        cr_assert_fail();
}

Test(run_exit, exit)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8};
    pid_t child = fork();
    int wstatus = 0;

    if (child == -1)
        cr_skip_test();
    if (child == 0) {
        run_exit(" 120", &sh);
    } else
        waitpid(child, &wstatus, 0);
    if (WIFEXITED(wstatus))
        cr_assert_eq(WEXITSTATUS(wstatus), 120);
    else
        cr_assert_fail();
}

Test(run_exit, exit_neg)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8};
    pid_t child = fork();
    int wstatus = 0;

    if (child == -1)
        cr_skip_test();
    if (child == 0) {
        run_exit(" -120", &sh);
        cr_assert_eq(sh.ex, -120);
    } else
        waitpid(child, &wstatus, 0);
}

Test(run_exit, exit_fail, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8};

    write(1, "\n", 1);
    run_exit(" 420 boys", &sh);
    cr_assert_stdout_eq_str("\nexit: Expression Syntax.\n");
    cr_assert_eq(sh.ex, 1);
}

Test(run_exit, exit_fail2, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8};

    write(1, "\n", 1);
    run_exit(" a", &sh);
    cr_assert_stdout_eq_str("\nexit: Expression Syntax.\n");
    cr_assert_eq(sh.ex, 1);
}

Test(run_exit, exit_fail3, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8};

    write(1, "\n", 1);
    run_exit(" 420b", &sh);
    cr_assert_stdout_eq_str("\nexit: Badly formed number.\n");
    cr_assert_eq(sh.ex, 1);
}

Test(check_end_shell, because_coverage)
{
    cr_assert_eq(check_end_shell(NULL, 0, 69), 69);
}
