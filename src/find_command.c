/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** find_command
*/

#include "my.h"

void free_command(struct data data, char *str)
{
    for (int i = 0; i < data.nbr_command; i++) {
        free(data.command[i]);
    }
    free(str);
}

static struct data find_command_3(struct data data, int i, int *ok)
{
    if (!my_strcmp(data.command[i], "setenv") && data.nbr_command == 1) {
        ok[0] = 1;
        data.exit_status = setenv_command(data, i);
    } else if (my_strcmp(data.command[i], "unsetenv") == 0) {
        data.exit_status = unsetenv_command(data, i);
        ok[0] = 1;
    } else {
        if (is_existing(data, data.command[i]) == NULL) {
            data.exit_status = put_command_not_found(data, i);
            ok[0] = 1;
        } else
            data.command[i] = is_existing(data, data.command[i]);
    }
    return (data);
}

static int find_command_2(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++)
        data = find_command_3(data, i, &ok);
    if (ok != 1)
        data.exit_status = do_command(data);
    return (data.exit_status);
}

static void do_exit(char **args)
{
    int nbr = 0;

    if (args != NULL && args[0] != NULL) {
        if (args[1] != NULL && args[1][0] != '\0') {
            nbr = my_getnbr(args[1]);
        }
    }
    if (isatty(0))
        my_putstr("exit\n");
    while (1)
        exit(nbr);
}

int find_command(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        if (my_strcmp(data.command[i], "exit") == 0 && data.nbr_command == 1)
            do_exit(data.args[i]);
        if (my_strcmp(data.command[i], "cd") == 0)
            return (cd_command(data, i));
        else
            ok = -1;
    }
    if (ok == -1)
        data.exit_status = find_command_2(data);
    return (data.exit_status);
}