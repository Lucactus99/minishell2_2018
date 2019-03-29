/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** command
*/

#include "my.h"

int open_type(int type, char *filename)
{
    if (type == 1)
        return (open(filename, O_CREAT|O_RDWR|O_TRUNC, 0644));
    if (type == 2)
        return (open(filename, O_CREAT|O_RDWR|O_APPEND, 0644));
    return (0);
}

static void check_command(struct data data)
{
    int out = open_type(data.redirection, data.redirection_name);

    if (data.nbr_command == 1) {
        if (data.redirection != 0)
            dup2(out, 1);
        if (execve(data.command[0], data.args[0], data.env) <= 0) {
            my_putstr_err(data.command[0]);
            my_putstr_err(": Permission denied.\n");
        }
    } else if (data.nbr_command == 2)
        do_command_simple_pipe(data);
    else
        do_command_double_pipes(data);
}

int do_command(struct data data)
{
    int status;

    if (fork() == 0 && data.path[0] != NULL) {
        check_binary(data);
        check_command(data);
        exit(1);
    } else
        wait(&status);
    data.exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status) == 1) {
        data.exit_status = status;
        print_error(status);
    }
    return (data.exit_status);
}