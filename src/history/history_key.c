/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** history_key.c
*/

#include "history.h"
#include "mysh.h"
#include "my.h"

char *no_str(int status, sh_t *sh, int *pos)
{
    char *buffer = NULL;
    FILE *fd = set_up_file(sh->env);

    if (fd == NULL)
        return NULL;
    buffer = get_last_line(fd);
    if (buffer == NULL)
        return NULL;
    fclose(fd);
    fd = set_up_file(sh->env);
    if (*pos == 0)
        *pos = atoi(buffer);
    else
        *pos = *pos + status;
    if (*pos < 1 || *pos > atoi(buffer))
        return NULL;
    sprintf(buffer, "%d", *pos);
    buffer = find_number(fd, buffer);
    fclose(fd);
    return (parser_command(buffer));
}

char *history_key(char *str, int status, sh_t *sh)
{
    static int pos = 0;

    if (status == 0) {
        pos = 0;
        return NULL;
    }
    if (str == NULL) {
        return (no_str(status, sh, &pos));
    }
    return NULL;
}