/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** lib header of my_ls
*/

#ifndef MY_H
#define MY_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define READ_SIZE (1)

int my_strlen(char const *str);
int my_tablen(char **ttab);
int my_strcmp(char *s1, char *s2);
int my_putnbr(int nb);
int my_nbrlen(long nb);
void int_to_str_static(int nb, char *str);
int my_isstreq(char *s1, char *s2);
char *my_strdup(char *str);
int my_getnbr(char const *str);
char **get_parse_str(char *str, int len, char c);
int get_len_str(char *str, char c);
void free_tab(char ***ttab);
char *my_sprintf(const char *format_string, char *s1, char *s2, char *s3);
char **str_to_word_array(char *str, char *delimiter);
char *get_next_line(int fd);

#endif
