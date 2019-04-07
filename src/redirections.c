/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redirections
*/

#include "my.h"

static int is_redirection_left(char *actual, int i)
{
    if (actual[i] == '>') {
        if (actual[i + 1] == '>')
            return (2);
        return (1);
    }
    return (0);
}

static int is_redirection_right(char *actual, int i)
{
    if (actual[i] == '<') {
        if (actual[i + 1] == '<')
            return (4);
        return (3);
    }
    return (0);
}

int is_redirection(char *actual)
{
    for (int i = 0; actual[i] != '\0'; i++) {
        if (is_redirection_left(actual, i) > 0)
            return (is_redirection_left(actual, i));
        if (is_redirection_right(actual, i) > 0)
            return (is_redirection_right(actual, i));
    }
    return (0);
}

static char *get_redirection_name(char *actual)
{
    int i = 0;
    int a = 0;
    char *str = malloc(sizeof(char) * my_strlen(actual));

    i = check_double_opposite_redirections(actual, i);
    if (i < 0)
        return (NULL);
    for (; actual[i] == ' '; i++);
    for (; actual[i] != '\0'; i++) {
        str[a] = actual[i];
        a++;
    }
    str[a] = '\0';
    if (my_strlen(str) <= 1) {
        my_putstr_err("Missing name for redirect.\n");
        return (NULL);
    }
    return (str);
}

struct data manage_redirection(struct data data, char *actual)
{
    char *ambiguous = NULL;

    if (data.redirection == 1 || data.redirection == 2 ||
    data.redirection == 3 || data.redirection == 4) {
        data.redirection_name = get_redirection_name(actual);
        if (data.redirection_name == NULL)
            data.exit_status = 1;
        ambiguous = is_ambiguous(actual);
        data = check_redirection_errors(data, ambiguous);
    }
    return (data);
}