/*
** EPITECH PROJECT, 2019
** history.h
** File description:
** lib header of 42sh
*/

#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

typedef struct input_s {
    char *cmd;
    int status;
    struct input_s *next;
} input_t;

void put_in_files(char *input, FILE *fd);
char *find_in_files(FILE *fd, char *input);
char *parser_command(char *buffer);
FILE *set_up_file(char **env);
input_t *set_up_input(char *input);
char *get_last_line(FILE *fd);
char *find_number(FILE *fd, char *str);
input_t *set_up_input(char *input);

#ifdef UNIT_TEST
#define LOAD_PATH strdup("./tests/ut/.t_42sh_history")
#else
#define LOAD_PATH my_sprintf("%s/%s", find_env_value("HOME", env, '='), \
".42sh_history", NULL)
#endif /* UNIT_TEST */

#endif
