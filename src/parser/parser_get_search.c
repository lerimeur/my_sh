/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_search
*/

#include "my.h"

char *get_search(char *str, char *search)
{
    int len = my_strlen(str);
    int search_len = my_strlen(search);
    int count = 0;
    char *result = NULL;

    if (str[0] != search[0])
        return (NULL);
    for (int i = 0; str[count++] == search[i] && i <= search_len; i += 1);
    if (count < search_len)
        return (NULL);
    str = &str[count - 1];
    for (len = 0; str[len] != '\0'; len += 1);
    result = calloc((len + 1), sizeof(char));
    if (result == NULL)
        return (NULL);
    for (int i = 0; i < len; i += 1)
        result[i] = str[i];
    result[len] = '\0';
    return (result);
}
