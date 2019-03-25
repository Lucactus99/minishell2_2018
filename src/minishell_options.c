/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_options
*/

#include "my.h"

char *useless_pipe(char *str)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(str) + 1));
    int a = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            if (str[i - 1] != ' ') {
                new_str[a] = ' ';
                a++;
            }
            new_str[a] = str[i];
            a++;
            if (str[i + 1] != ' ') {
                new_str[a] = ' ';
                a++;
            }
        } else {
            new_str[a] = str[i];
            a++;
        }
    }
    return (new_str);
}

char *remove_useless(char *str)
{
    int i = 0;
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
        new_str[d] = 0;
    return (useless_pipe(new_str));
}

void print_error_6(int status)
{
    if (WTERMSIG(status) == 44)
        my_putstr_err("Signal 44\n");
    if (WTERMSIG(status) == 45)
        my_putstr_err("Signal 45\n");
    if (WTERMSIG(status) == 46)
        my_putstr_err("Signal 46\n");
    if (WTERMSIG(status) == 47)
        my_putstr_err("Signal 47\n");
    if (WTERMSIG(status) == 48)
        my_putstr_err("Signal 48\n");
}

void print_error_5(int status)
{
    if (WTERMSIG(status) == 35)
        my_putstr_err("Second Realtime Signal\n");
    if (WTERMSIG(status) == 36)
        my_putstr_err("Third Realtime Signal\n");
    if (WTERMSIG(status) == 37)
        my_putstr_err("Fourth Realtime Signal\n");
    if (WTERMSIG(status) == 38)
        my_putstr_err("Signal 38\n");
    if (WTERMSIG(status) == 39)
        my_putstr_err("Signal 39\n");
    if (WTERMSIG(status) == 40)
        my_putstr_err("Signal 40\n");
    if (WTERMSIG(status) == 41)
        my_putstr_err("Signal 41\n");
    if (WTERMSIG(status) == 42)
        my_putstr_err("Signal 42\n");
    if (WTERMSIG(status) == 43)
        my_putstr_err("Signal 43\n");
    print_error_6(status);
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