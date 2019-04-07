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

int is_builtin(struct data data, int i)
{
    if (my_strcmp(data.command[i], "setenv") == 0 ||
    my_strcmp(data.command[i], "env") == 0) {
        print_env(data.env);
        return (1);
    }
    if (my_strcmp(data.command[i], "cd") == 0) {
        cd_command(data, i);
        return (1);
    }
    if (my_strcmp(data.command[i], "exit") == 0)
        return (1);
    return (0);
}

static void check_command(struct data data)
{
    int out = open_type(data.redirection, data.redirection_name);

    if (data.nbr_command == 1) {
        check_binary(data);
        if (data.redirection != 0)
            dup2(out, 1);
        if (data.redirection == 3 || data.redirection == 4)
            data.args[0] = add_args(data.args[0], data.redirection_name);
        if (execve(data.command[0], data.args[0], data.env) < 0) {
            my_putstr_err(data.command[0]);
            my_putstr_err(": Permission denied.\n");
        }
    } else {
        for (int i = 0; i < data.nbr_command; i++)
            do_pipe(data, i);
    }
}

int do_command(struct data data)
{
    int status;

    if (fork() == 0 && data.path[0] != NULL) {
        check_command(data);
        exit(0);
    } else
        wait(&status);
    data.exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status) == 1) {
        data.exit_status = status;
        print_error(status);
    }
    return (data.exit_status);
}