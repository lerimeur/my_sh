/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Unit Tests for {cd.c}.
*/

#include "unit_tests.h"
#include "mysh.h"
#include "parser.h"

extern char **environ;

Test(my_swap, a_is_null)
{
    char *a = NULL;
    char *b = strdup("hello world\n");

    my_swap(&a, &b);
    cr_assert_str_eq(a, "hello world\n");
    cr_assert_null(b);
    free(a);
}

Test(my_swap, b_is_null)
{
    char *a = strdup("hello world\n");
    char *b = NULL;

    my_swap(&a, &b);
    cr_assert_null(a);
    cr_assert_str_eq(b, "hello world\n");
    free(b);
}

Test(my_swap, both_are_null)
{
    char *a = NULL;
    char *b = NULL;

    my_swap(&a, &b);
    cr_assert_null(a);
    cr_assert_null(b);
}

Test(my_swap, valid)
{
    char *a = strdup("bonjour");
    char *b = strdup("hello world\n");

    my_swap(&a, &b);
    cr_assert_str_eq(a, "hello world\n");
    cr_assert_str_eq(b, "bonjour");
    free(a);
    free(b);
}

Test(get_pwd, test)
{
    char **pwd = get_pwd(NULL);
    char *cwd = getcwd(NULL, 0);

    cr_assert_str_eq(pwd[0], cwd);
    cr_assert_str_eq(pwd[1], "\0");
    cr_assert_null(pwd[2]);
}

Test(nb_char, test)
{
    int nb = nb_char("hello world", 'l');

    cr_assert_eq(nb, 4);
}

Test(run_cd, too_much_arg, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};

    run_cd(" lol ol", &sh);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
    cr_assert_eq(sh.ex, 1);
}

Test(run_cd, fail, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *pwd;
    char *oldpwd;

    sh.pwd = get_pwd(NULL);
    if (!sh.pwd)
        cr_skip_test();
    pwd = strdup(sh.pwd[0]);
    oldpwd = strdup(sh.pwd[1]);
    if (!pwd || !oldpwd)
        cr_skip_test();
    run_cd(" lol", &sh);
    cr_assert_str_eq(sh.pwd[0], pwd);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], oldpwd);
    cr_assert_stderr_eq_str("lol: No such file or directory.\n");
}

Test(run_cd, fail2, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *pwd;
    char *oldpwd;

    sh.pwd = get_pwd(NULL);
    if (!sh.pwd)
        cr_skip_test();
    pwd = strdup(sh.pwd[0]);
    oldpwd = strdup(sh.pwd[1]);
    if (!pwd || !oldpwd)
        cr_skip_test();
    run_cd(" Makefile", &sh);
    cr_assert_str_eq(sh.pwd[0], pwd);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], oldpwd);
    cr_assert_stderr_eq_str("Makefile: Not a directory.\n");
}

Test(run_cd, src)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char nwd[1024];
    char *cwd = getcwd(NULL, 0);
    size_t i = 0;

    getcwd(nwd, 1024);
    sh.pwd = get_pwd(NULL);
    if (!sh.pwd)
        cr_skip_test();
    for (; nwd[i]; i += 1);
    nwd[i++] = '/';
    nwd[i++] = 's';
    nwd[i++] = 'r';
    nwd[i++] = 'c';
    nwd[i] = '\0';
    run_cd(" src", &sh);
    cr_assert_str_eq(sh.pwd[0], nwd);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], cwd);
}

Test(run_cd, home)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *cwd = getcwd(NULL, 0);

    sh.home = find_env_value("HOME", sh.env, '=');
    sh.pwd = get_pwd(NULL);
    if (!sh.home || !sh.pwd)
        cr_skip_test();
    run_cd("", &sh);
    cr_assert_str_eq(sh.pwd[0], sh.home);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], cwd);
}

Test(run_cd, back)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *pwd = getenv("PWD");
    char *oldpwd = getenv("OLDPWD");

    sh.pwd = malloc(3 * sizeof(char *));
    if (!sh.pwd)
        cr_skip_test();
    sh.pwd[0] = pwd;
    sh.pwd[1] = oldpwd;
    sh.pwd[2] = NULL;
    if (!sh.pwd[0] || !sh.pwd[1])
        cr_skip_test();
    run_cd(" -", &sh);
    cr_assert_str_eq(sh.pwd[0], oldpwd);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], pwd);
}

Test(run_cd, back_no_dir, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *pwd = getenv("PWD");
    char *oldpwd = strdup("lol");

    sh.pwd = malloc(3 * sizeof(char *));
    if (!sh.pwd)
        cr_skip_test();
    sh.pwd[0] = pwd;
    sh.pwd[1] = oldpwd;
    sh.pwd[2] = NULL;
    if (!sh.pwd[0] || !sh.pwd[1])
        cr_skip_test();
    run_cd(" -", &sh);
    cr_assert_str_eq(sh.pwd[0], pwd);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], oldpwd);
    cr_assert_stderr_eq_str("lol: No such file or directory.\n");
}

Test(run_cd, back_not_dir, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, environ, NULL, NULL, NULL, NULL, NULL, 0};
    char *cwd = getcwd(NULL, 0);
    char *oldpwd;
    char exp[1024];

    sh.pwd = malloc(3 * sizeof(char));
    sh.pwd[0] = strdup(cwd);
    sh.pwd[1] = malloc((strlen(cwd) + 10) * sizeof(char));
    sh.pwd[1] = strcat(sh.pwd[1], cwd);
    oldpwd = strcat(sh.pwd[1], "/Makefile");
    sh.pwd[2] = NULL;
    sprintf(exp, "%s%s\n", oldpwd, ": Not a directory.");
    if (!sh.pwd || !sh.pwd[0] || !sh.pwd[1] || !exp)
        cr_skip_test();
    run_cd(" -", &sh);
    cr_assert_str_eq(sh.pwd[0], cwd);
    cr_assert_str_eq(sh.pwd[0], getcwd(NULL, 0));
    cr_assert_str_eq(sh.pwd[1], oldpwd);
    cr_assert_stderr_eq_str(exp);
}
