/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exit_function
*/

#include "mysh.h"
#include "my.h"

static int my_str_isnum(char const *str)
{
    int result = 1;

    for (int i = 0; str[i] != '\0'; i += 1)
        result += (((str[i] >= '0' && str[i] <= '9') || str[i] == '-') ? 0 : 1);
    if (result == 1)
        return (1);
    else
        return (0);
}

static int error_exit(char *line, int ex)
{
    if (my_str_isnum(line) == 0) {
        if (CHAR_IS_NUM(line[0]) == 1) {
            printf("exit: Badly formed number.\n");
            return (-1);
        } else if (CHAR_IS_NUM(line[0]) == 0) {
            printf("exit: Expression Syntax.\n");
            return (-1);
        }
    } else {
        ex = my_getnbr(line);
        write(0, "exit\n", 5);
    }
    return (ex);
}

STATIC int check_end_shell(char *line, int ac, int ex)
{
    if (ac > 1) {
        printf("exit: Expression Syntax.\n");
        return (-1);
    } else if (ac == 1)
        return (error_exit(line, ex));
    return (ex);
}

void run_exit(char *cmd, UNUSED sh_t *sh)
{
    if (cmd[0] != '\0')
        sh->ex = check_end_shell(&cmd[1], nb_params(cmd), sh->ex);
    if (sh->ex == -1) {
        sh->ex = 1;
        return;
    }
    exit(sh->ex);
}
