/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** options
*/

#include "my.h"

static char *put_space(char *new_str, char *str, int *a, int i)
{
    if (str[i - 1] != ' ') {
        new_str[a[0]] = ' ';
        a[0]++;
    }
    new_str[a[0]] = str[i];
    a[0]++;
    if (str[i + 1] != ' ') {
        new_str[a[0]] = ' ';
        a[0]++;
    }
    return (new_str);
}

static char *useless_pipe(char *str)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(str) + 1));
    int a = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            new_str = put_space(new_str, str, &a, i);
        } else {
            new_str[a] = str[i];
            a++;
        }
    }
    new_str[a] = '\0';
    return (new_str);
}

#define IS_WHITESPACE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r' ? 1 : 0)

char *clean_str(char *str)
{
    size_t idx = 0;

    for (size_t i = 0; str[i]; ++i) {
        if (!IS_WHITESPACE(str[i])) {
            str[idx++] = str[i];
        } else if (idx && str[i + 1] && !IS_WHITESPACE(str[i + 1])) {
            str[idx++] = ' ';
        }
    }
    str[idx] = '\0';
    return (str);
}

char *remove_useless(char *str)
{
    /*int i = 0;
    int a = 0;
    char *new_str = malloc(sizeof(char) * (my_strlen(str) + 1));

    for (; str[0] == ' ' || str[0] == '\t'; str++);
    for (; str[i] != '\0'; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
        if (((str[i] == ' ' || str[i] == '\t') && str[i + 1] != ' ' &&
        str[i + 1] != '\t') || (str[i] != ' ' && str[i] != '\t')) {
            new_str[a] = str[i];
            a++;
        }
    }
    new_str[a] = 0;
    for (int d = my_strlen(new_str) - 1; new_str[d] == ' '; d--)
        new_str[d] = 0;*/
    return (useless_pipe(clean_str(str)));
}

char **add_env(struct data data, int command)
{
    int j = 0;

    for (; data.env[j] != NULL; j++);
    data.env[j] = malloc(sizeof(char) * 20);
    data.env[j] = my_strcpy(data.env[j], data.args[command][1]);
    data.env[j] = my_strcat(data.env[j], "=");
    for (int i = 2; i <= data.nbr_args[command]; i++)
        data.env[j] = my_strcat(data.env[j], data.args[command][i]);
    data.env[j + 1] = 0;
    return (data.env);
}