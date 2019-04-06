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

int do_pipe_first(struct data data, int i, int pipes[], int out)
{
    if (data.command[i + 1] != NULL)
        dup2(pipes[1], 1);
    else {
        if (data.redirection != 0)
            dup2(out, 1);
    }
    close(pipes[0]);
    if (my_strcmp(data.command[i], "setenv") == 0)
        print_env(data.env);
    else if (my_strncmp(data.command[i], "./", 2) == 0)
        do_binary(data, i);
    else {
        if (execve(data.command[i], data.args[i], data.env) < 0) {
            my_putstr_err(data.command[0]);
            my_putstr_err(": Permission denied.\n");
        }
    }
    return (out);
}

void do_pipe(struct data data, int i)
{
    int pipes[2];
    int out = open_type(data.redirection, data.redirection_name);
    static int fd_in = 0;

    pipe(pipes);
    if (fork() == 0) {
        dup2(fd_in, 0);
        out = do_pipe_first(data, i, pipes, out);
        exit(0);
    } else {
        wait(NULL);
        close(pipes[1]);
        fd_in = pipes[0];
        if (data.command[i + 1] == NULL) {
            close(out);
            close(pipes[0]);
            close(fd_in);
            exit(0);
        }
    }
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