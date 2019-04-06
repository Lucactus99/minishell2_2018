/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** find_command
*/

#include "my.h"

static int find_command_2(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        if (my_strcmp(data.command[i], "setenv") == 0 && data.nbr_command == 1) {
            ok = 1;
            data.exit_status = setenv_command(data, i);
            if (data.exit_status == 1)
                return (data.exit_status);
        } else if (my_strcmp(data.command[i], "unsetenv") == 0) {
            data.exit_status = unsetenv_command(data, i);
            ok = 1;
        } else {
            if (is_existing(data, data.command[i]) == NULL) {
                data.exit_status = put_command_not_found(data, i);
                ok = 1;
            } else
                data.command[i] = is_existing(data, data.command[i]);
        }
    }
    if (ok != 1)
        data.exit_status = do_command(data);
    return (data.exit_status);
}

static void do_exit(void)
{
    if (isatty(0))
        my_putstr("exit\n");
    while (1)
        exit(0);
}

static int check_cd_env(struct data data, int i)
{
    if (my_strcmp(data.command[i], "cd") == 0)
        return (cd_command(data, i));
    else
        return (-1);
    return (0);
}

int find_command(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        if (my_strcmp(data.command[i], "exit") == 0)
            do_exit();
        else {
            ok = check_cd_env(data, i);
            if (ok != -1)
                data.exit_status = ok;
            if (ok == 2)
                return (0);
        }
    }
    if (ok == -1)
        data.exit_status = find_command_2(data);
    return (data.exit_status);
}