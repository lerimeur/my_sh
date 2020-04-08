/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check history
*/

#include "mysh.h"
#include "history.h"
#include "parser.h"

char *check_history_call(char **ccmd, sh_t *sh)
{
    char *cmd = *ccmd;
    char *buff = NULL;
    int len = 0;

    for (int i = 0; cmd[i]; i += 1) {
            if (cmd[i] != '!')
                continue;
            buff = run_history_seach(&cmd[i], sh);
            if (!buff)
                continue;
            for (len = 0; cmd[i + len] &&
            cmd[i + len] != ' ' && cmd[i + len] != '\t'; len += 1);
            cmd = replace_in_str(cmd, buff, i, len);
        }
    return (cmd);
}
