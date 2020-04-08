/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** .
*/

#include "unit_tests.h"
#include "mysh.h"
#include "prompt.h"

extern char **environ;

Test(call_cmd, command_fail, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("lol", &sh);
    cr_assert_stdout_eq_str("\nlol: Command not found.\n");
    cr_assert_null(sh.previous_line);
}

Test(call_cmd, command_fail_2, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo bonjour", &sh);
    cr_assert_str_eq(sh.previous_line, "echo bonjour");
    call_cmd("lol", &sh);
    cr_assert_str_eq(sh.previous_line, "echo bonjour");
    call_cmd("echo hello world\n", &sh);
    cr_assert_str_eq(sh.previous_line, "echo hello world\n");
    cr_assert_stdout_eq_str("\nbonjour\nhello world\n\n");
    cr_assert_stderr_eq_str("lol: Command not found.\n");
}

Test(call_cmd, simple_command, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo hello world", &sh);
    cr_assert_stdout_eq_str("\nhello world\n");
    cr_assert_str_eq(sh.previous_line, "echo hello world");
}

Test(call_cmd, simple_pipe, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo hello world | cat -e", &sh);
    cr_assert_stdout_eq_str("\nhello world$\n");
    cr_assert_str_eq(sh.previous_line, "echo hello world | cat -e");
}

Test(call_cmd, simple_semicolon, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo hello world ; echo lol", &sh);
    cr_assert_stdout_eq_str("\nhello world\nlol\n");
    cr_assert_str_eq(sh.previous_line, "echo hello world ; echo lol");
}

Test(call_cmd, multiple_command, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo hello world | cat -e", &sh);
    cr_assert_str_eq(sh.previous_line, "echo hello world | cat -e");
    call_cmd("set", &sh);
    cr_assert_stdout_eq_str("\nhello world$\n_\techo hello world | cat \
-e\n");
    cr_assert_str_eq(sh.previous_line, "set");
}

Test(call_cmd, alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc_callcmd") + 1,
    "tests/ut/.t_42shrc_callcmd");
    if (!sh.alias)
        cr_skip_test();
    write(1, "\n", 1);
    call_cmd("hw | cat -e", &sh);
    cr_assert_str_eq(sh.previous_line, "hw | cat -e");
    call_cmd("set", &sh);
    cr_assert_stdout_eq_str("\nhello world$\n_\techo hello world | cat \
-e\n");
    cr_assert_str_eq(sh.previous_line, "set");
}

Test(call_cmd, history, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo hello world", &sh);
    cr_assert_str_eq(sh.previous_line, "echo hello world");
    call_cmd("!echo", &sh);
    cr_assert_str_eq(sh.previous_line, "!echo");
}

Test(call_cmd, which, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("which pwd", &sh);
    cr_assert_str_eq(sh.previous_line, "which pwd");
    cr_assert_stdout_eq_str("\n/usr/bin/pwd\n");
}

Test(call_cmd, which_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc_callcmd") + 1,
    "tests/ut/.t_42shrc_callcmd");
    cr_skip_test();
    write(1, "\n", 1);
    call_cmd("which hw", &sh);
    cr_assert_str_eq(sh.previous_line, "which hw");
    write(1, "\n", 1);
    cr_assert_stdout_eq_str("\nhw:\taliased to echo hello world\n\n");
}

Test(call_cmd, where, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("where pwd", &sh);
    cr_assert_str_eq(sh.previous_line, "where pwd");
    cr_assert_stdout_eq_str("\n/usr/bin/pwd\n/usr/pwd\n");
}

Test(call_cmd, globbing_all, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo */*.c", &sh);
    cr_assert_str_eq(sh.previous_line, "echo */*.c");
    cr_assert_stdout_eq_str("\nmain/main.c src/builtins_hub_bis.c \
src/cleanstr.c src/hub_check_history.c src/hub_tools.c src/minishell_hub.c \
src/utils.c\n");
}

Test(call_cmd, globbing_range, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("echo */[abcmjk]*.c", &sh);
    cr_assert_str_eq(sh.previous_line, "echo */[abcmjk]*.c");
    cr_assert_stdout_eq_str("\nmain/main.c src/builtins_hub_bis.c \
src/cleanstr.c src/minishell_hub.c\n");
}

Test(call_cmd, dollar, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("set lol=lil ; $lol ; echo $lol", &sh);
    cr_assert_str_eq(sh.previous_line, "set lol=lil ; $lol ; echo $lol");
}

Test(call_cmd, dollar_fail, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    write(1, "\n", 1);
    call_cmd("$lol", &sh);
    cr_assert_null(sh.previous_line);
    call_cmd("echo $lol", &sh);
    cr_assert_null(sh.previous_line);
    cr_assert_stdout_eq_str("\nlol: Undefined variable.\nlol: Undefined \
variable.\n");
}

Test(call_cmd, where_alias, .init = redirect_all_stdout)
{
    sh_t sh = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    sh.env = environ;
    sh.alias = load_alias(get_nb_line("tests/ut/.t_42shrc_callcmd") + 1,
    "tests/ut/.t_42shrc_callcmd");
    if (!sh.alias)
        cr_skip_test();
    write(1, "\n", 1);
    call_cmd("where hw", &sh);
    cr_assert_str_eq(sh.previous_line, "where hw");
    cr_assert_stdout_eq_str("\nhw is aliased to echo hello world\n");
}
