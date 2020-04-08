/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "my.h"
#include "mysh.h"
#include "prompt.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

void replace_in_line(char **line, char *new)
{
    int i = 0;
    int j;

    *line = my_realloc(*line, strlen(new));
    j = strlen(*line) - 1;
    for (; j >= 0; j--)
        if ((*line)[j] == new[0] || j == 0)
            break;
    for (i = 0; new[i]; i++) {
        (*line)[j] = new[i];
        j++;
    }
    (*line)[j] = '\0';
}

int count_matching_files(DIR *dir, char *tmp, struct dirent *dirent,
char *tmp2)
{
    int nb = 0;

    dir = opendir(tmp);
    if (dir == NULL)
        return 0;
    dirent = readdir(dir);
    while (dirent != NULL) {
        if (file_match(dirent->d_name, tmp2))
            nb += 1;
        dirent = readdir(dir);
    }
    closedir(dir);
    return (nb);
}

void open_and_cmp_files(char *tmp, char *tmp2, char **line, int nb)
{
    struct dirent *dirent = NULL;
    DIR *dir = NULL;

    nb = count_matching_files(dir, tmp, dirent, tmp2);
    if (nb == 0)
        return;
    if (nb > 1)
        my_putchar_0('\n');
    dir = opendir(tmp);
    if (dir == NULL)
        return;
    for (dirent = readdir(dir); dirent != NULL; dirent = readdir(dir)) {
        if (file_match(dirent->d_name, tmp2)) {
            if (nb == 1)
                return (replace_in_line(line, dirent->d_name));
            if (nb > 1)
                dprintf(0, "%s ", dirent->d_name);
        }
    }
    closedir(dir);
}

void auto_complete_given_path(char *tmp, int index, char *tmp2, char **line)
{
    int i = 0;
    int j = 0;

    if (tmp == NULL || tmp2 == NULL)
        exit(84);
    while (index > 0 && tmp[index] != '/')
        index--;
    j = index;
    index += 1;
    for (; tmp[index] != '\0'; index++, i++)
        tmp2[i] = tmp[index];
    tmp2[i] = '\0';
    tmp[j + 1] = '\0';
    open_and_cmp_files(tmp, tmp2, line, 0);
}

void auto_complete_path(char **line)
{
    char **arr = str_to_word_array(*line, " \t");
    int arr_len = my_tablen(arr);
    char *tmp2 = NULL;
    char *tmp = NULL;
    int index = 0;

    if (arr_len == 0)
        return;
    tmp2 = strdup(arr[arr_len - 1]);
    tmp = strdup(arr[arr_len - 1]);
    index = strlen(arr[arr_len - 1]) - 1;
    if (is_filepath(*line))
        auto_complete_given_path(tmp, index, tmp2, line);
    else
        open_and_cmp_files(".", tmp2, line, 0);
    free(tmp);
    free(tmp2);
    free_tab(&arr);
}