/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** manage
*/

#include "my.h"

static struct data manage_command_fill(struct data data, char *actual)
{
    if (data.redirection_name != NULL || data.redirection == 0) {
        data.nbr_args = malloc(sizeof(int) * data.nbr_command);
        for (int i = 0; data.command[i]; i++)
            data.nbr_args[i] = get_nbr_args(data.command[i]);
        data.args = put_args(data.command, data.nbr_command);
        for (int i = 0; data.command[i]; i++)
            data.command[i] = get_program_name(data.command[i]);
        data.exit_status = find_command(data);
        free_command(data, actual);
    }
    return (data);
}

static struct data manage_command_type(struct data data, char *actual)
{
    if (data.nbr_command == 84) {
        my_putstr_err("Invalid null command.\n");
        data.exit_status = 1;
    } else {
        data.command = malloc(sizeof(char *) * (data.nbr_command + 1));
        data.command = get_tab_command(data, actual);
        data = manage_redirection(data, actual);
        data = manage_command_fill(data, actual);
    }
    return (data);
}

struct data manage_user_input(struct data data, char *str)
{
    char *actual = NULL;

    actual = get_actual_command_line(str);
    if (count_commands(str) == 84) {
        my_putstr_err("Invalid null command.\n");
        actual = get_actual_command_line(str);
        actual = NULL;
        str = "lucas";
        data.exit_status = 1;
    }
    while (actual != NULL) {
        actual = clean_str(actual);
        data.nbr_command = count_commands(actual);
        data.redirection = is_redirection(actual);
        data = manage_command_type(data, actual);
        actual = get_actual_command_line(str);
    }
    return (data);
}

static int is_whitespace(char c)
{
    if (c == '\t' || c == ' ' || c == '\n' || c == '\r')
        return (1);
    return (0);
}

char *clean_str(char *str)
{
    size_t idx = 0;

    for (size_t i = 0; str[i]; ++i) {
        if (!is_whitespace(str[i])) {
            str[idx++] = str[i];
        } else if (idx && str[i + 1] && !is_whitespace(str[i + 1])) {
            str[idx++] = ' ';
        }
    }
    str[idx] = '\0';
    return (useless_pipe(str));
}