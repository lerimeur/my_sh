/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cleans input
*/

#include "mysh.h"
#include "my.h"

static int shift_in_str(char *input, int correct, bool in_str)
{
    if (in_str)
        return (correct);
    while (input[correct] != '\0' && (((input[correct] == ' '
    || input[correct] == '\t') && ((input[correct + 1] == '\t'
    || input[correct + 1] == ' '))) || (input[correct] == ';'
    && input[correct + 1] == ';')))
            correct += 1;
    return (correct);
}

static void add_end_str(char *str, int len)
{
    if (len <= 0)
        return;
    for (; str[len] == ' ' || str[len] == '\t' || str[len] == ';'; len -= 1)
        str[len] = '\0';
}

static int start_after_garbage(char *input, int correct)
{
    return (input[correct] != '\0' && (input[correct] == ' '
    || input[correct] == '\t' || input[correct] == ';'));
}

static void get_loop(char *input, int correct, bool *in_str)
{
    if (input[correct] == '\t')
        input[correct] = ' ';
    if (input[correct] == '"')
        *in_str = (!(*in_str) ? true : false);
}

char *clean_str(char **str)
{
    char *input = *str;
    int correct = 0;
    int len = my_strlen(input);
    char *new_value = calloc((len + 1), sizeof(char));
    int i = 0;
    bool in_str = false;

    if (new_value == NULL)
        return (NULL);
    for (correct = 0; start_after_garbage(input, correct); correct += 1);
    for (; input[correct] != '\0'; i += 1) {
        correct = shift_in_str(input, correct, in_str);
        if (input[correct] == '\0')
            break;
        get_loop(input, correct, &in_str);
        new_value[i] = input[correct++];
    }
    for (; new_value[i - 1] == ';'; i -= 1);
    for (; i <= len; new_value[i++] = '\0');
    add_end_str(new_value, my_strlen(new_value) - 1);
    return (new_value);
}
