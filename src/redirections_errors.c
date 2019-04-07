/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redirections_errors
*/

#include "my.h"

char *is_ambiguous(char *str)
{
    if (count_redirections(str) == 1)
        return ("right");
    if (count_redirections(str) == 2)
        return ("left");
    if (count_redirections(str) == 3)
        return ("missing");
    if (pipe_after_redirection(str) == 1)
        return ("right");
    return (str);
}

int check_redirections(int counter_right, int counter_left, char *str)
{
    if (counter_right > 1)
        return (1);
    if (counter_left > 1)
        return (2);
    if (counter_left + counter_right > 1) {
        if (counter_left > counter_right)
            return (2);
        else
            return (1);
    }
    if (str[my_strlen(str) - 1] == '>' || str[my_strlen(str) - 1] == '<')
        return (3);
    return (0);
}

int check_double_opposite_redirections(char *actual, int i)
{
    for (; actual[i] != '>' && actual[i] != '<' && actual[i] != '\0'; i++);
    if ((actual[i] == '>' && actual[i + 1] == '<') ||
    (actual[i] == '<' && actual[i + 1] == '>')) {
        my_putstr_err("Missing name for redirect.\n");
        return (-1);
    }
    i++;
    if (actual[i] == '>' || actual[i] == '<')
        i++;
    if (actual[i] == '>' || actual[i] == '<') {
        my_putstr_err("Missing name for redirect.\n");
        return (-1);
    }
    return (i);
}

struct data check_redirection_errors(struct data data, char *ambiguous)
{
    if (my_strcmp("left", ambiguous) == 0 &&
    data.redirection_name != NULL) {
        my_putstr_err("Ambiguous input redirect.\n");
        data.redirection_name = NULL;
        data.exit_status = 1;
    }
    if (my_strcmp("right", ambiguous) == 0 &&
    data.redirection_name != NULL) {
        my_putstr_err("Ambiguous output redirect.\n");
        data.redirection_name = NULL;
        data.exit_status = 1;
    }
    if (my_strcmp("missing", ambiguous) == 0 &&
    data.redirection_name != NULL) {
        my_putstr_err("Missing name for redirect.\n");
        data.redirection_name = NULL;
        data.exit_status = 1;
    }
    return (data);
}