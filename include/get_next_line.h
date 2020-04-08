/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** Header of get_next_line
*/

#ifndef HEADER_H
#define HEADER_H
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#ifndef READ_SIZE
#define READ_SIZE (1)
#endif
char *get_next_line(int fd);
#endif
