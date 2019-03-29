/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** binary
*/

#include "my.h"

static int do_binary(struct data data, int command)
{
    data.command[command] += 2;
    if (execve(data.command[command], data.args[command], data.env) <= 0) {
        if (errno == 8) {
            my_putstr_err("./");
            my_putstr_err(data.command[command]);
            my_putstr_err(": Exec format error. Wrong Architecture.\n");
        } else if (errno == 2) {
            my_putstr_err("./");
            my_putstr_err(data.command[command]);
            my_putstr_err(": Command not found.\n");
        } else {
            my_putstr_err("./");
            my_putstr_err(data.command[command]);
            my_putstr_err(": Permission denied.\n");
        }
    }
    exit(0);
}

void check_binary(struct data data)
{
    for (int i = 0; i < data.nbr_command; i++) {
        if (my_strncmp(data.command[i], "./", 2) == 0)
            do_binary(data, i);
    }
}