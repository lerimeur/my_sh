/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** main_history.c
*/

#include "history.h"
#include "mysh.h"
#include "my.h"

STATIC void print_history(char **env)
{
    char *path = LOAD_PATH;
    FILE *fp = fopen(path, "r");
    char *buffer = NULL;
    size_t len;

    if (fp == NULL) {
        free(path);
        return;
    }
    while (getline(&buffer, &len, fp) != -1) {
        printf("%s", buffer);
    }
    fclose(fp);
    free(path);
}

FILE *set_up_file(char **env)
{
    static int status = 0;
    FILE *fp = NULL;
    char *path = LOAD_PATH;
    mode_t mode = {S_IRWXU | S_IRGRP | S_IROTH};

    if (status == 0) {
        creat(path, mode);
        status++;
    }
    fp = fopen(path, "r+");
    if (fp == NULL) {
        free(path);
        return (NULL);
    }
    free(path);
    return (fp);
}

char *run_history_part_two(char *cmd, FILE *fd)
{
    char *buffer = NULL;

    if (cmd[0] == '!') {
        buffer = find_in_files(fd, &cmd[1]);
        if (buffer == NULL) {
            dprintf(1, "%s: Event not found.\n", &cmd[1]);
            return (NULL);
        }
        for (int i = my_strlen(buffer) - 1; i > 0
        && (buffer[i] == '\n' || buffer[i] == ' ' ||
        buffer[i] == '\t'); i -= 1)
            buffer[i] = '\0';
        for (int i = 0; i < my_strlen(buffer) &&
        (buffer[i] == ' ' || buffer[i] == '\t'); i += 1)
            buffer++;
        fclose(fd);
        return (buffer);
    }
    return NULL;
}

char *run_history_seach(char *cmd, sh_t *sh)
{
    FILE *fd = set_up_file(sh->env);
    char *buffer = NULL;

    if (fd == NULL)
        return (NULL);
    if ((buffer = run_history_part_two(cmd, fd)) == NULL) {
        fclose(fd);
        return (NULL);
    }
    return buffer;
}

void run_history(char *cmd, sh_t *sh)
{
    (void)cmd;
    print_history(sh->env);
    return;
}
