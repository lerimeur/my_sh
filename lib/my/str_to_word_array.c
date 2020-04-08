/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** char * -> char **
*/

#include "my.h"

static bool is_in_delim(char *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (c == str[i])
            return (true);
    return (false);
}

static char *get_word(char *str, int i, char *delimiter)
{
    char *word = NULL;
    int len = 0;
    int z = 0;

    for (int j = i; is_in_delim(delimiter, str[j]) == false; j++) {
        len++;
        if (str[j] == '\0')
            break;
    }
    if (len != 0)
        word = malloc(sizeof(char) * (len + 1));
    if (word == NULL)
        return (NULL);
    for (int a = i; z != len; z++, a++)
        word[z] = str[a];
    word[z] = '\0';
    i += len + 1;
    return (word);
}

static int get_nb_word(char *str, char *limit)
{
    int space = 0;

    for (int i = 0; str[i]; i++)
        if (is_in_delim(limit, str[i]) == true)
            space++;
    return (space + 1);
}

char **str_to_word_array(char *str, char *delimiter)
{
    int i = 0;
    int len = 0;
    int nwords = 0;
    char **tab = NULL;
    char *word = NULL;

    if (str == NULL)
        return (NULL);
    nwords = get_nb_word(str, delimiter);
    tab = malloc(sizeof(*tab) * (nwords + 1));
    if (tab == NULL)
        return (NULL);
    for (; i != nwords; i++) {
        word = get_word(str, len, delimiter);
        len += (my_strlen(word) + 1);
        tab[i] = word;
    }
    tab[i] = NULL;
    return (tab);
}