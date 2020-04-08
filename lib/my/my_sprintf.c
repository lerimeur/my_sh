/*
** EPITECH PROJECT, 2018
** my_strcat
** File description:
** Concatenates two strings
*/

#include "my.h"
#include <stdio.h>
#include <stdarg.h>

char *my_sprintf(const char *format_string, char *s1, char *s2, char *s3)
{
    int len = 1 + my_strlen(s1) + my_strlen(s2) + my_strlen(s3)
    + my_strlen(format_string)
    - (s1 == NULL ? 2 : 0) - (s2 == NULL ? 2 : 0) - (s3 == NULL ? 2 : 0);
    char *result_string = calloc(len, (sizeof(char)));

    if (result_string == NULL)
        return (NULL);
    sprintf(result_string, format_string, s1, s2, s3);
    return (result_string);
}
