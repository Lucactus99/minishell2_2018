/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** errors_2
*/

#include "my.h"

int check_error_pipe(char *str, int i)
{
    for (; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '|')
            return (0);
    }
    return (84);
}

int put_command_not_found(struct data data, int i)
{
    my_putstr_err(data.command[i]);
    my_putstr_err(": Command not found.\n");
    return (1);
}

static void print_error_6(int status)
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