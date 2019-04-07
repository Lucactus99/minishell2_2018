/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** binary
*/

#include "my.h"

static int do_pipe_first(struct data data, int i, int pipes[], int out)
{
    if (data.command[i + 1] != NULL)
        dup2(pipes[1], 1);
    else {
        if (data.redirection != 0)
            dup2(out, 1);
    }
    close(pipes[0]);
    if (is_builtin(data, i) == 1)
        return (out);
    if (my_strncmp(data.command[i], "./", 2) == 0)
        do_binary(data, i);
    else {
        if (execve(data.command[i], data.args[i], data.env) < 0) {
            my_putstr_err(data.command[0]);
            my_putstr_err(": Permission denied.\n");
        }
    }
    return (out);
}

static void close_fd_pipes(int out, int pipes[], int fd_in)
{
    close(out);
    close(pipes[0]);
    close(fd_in);
    for (int i = 0; i < 2; i++)
        wait(NULL);
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
        close(pipes[1]);
        fd_in = pipes[0];
        if (data.command[i + 1] == NULL) {
            close_fd_pipes(out, pipes, fd_in);
            exit(0);
        }
    }
}

int do_binary(struct data data, int command)
{
    data.command[command] += 2;
    if (execve(data.command[command], data.args[command], data.env) <= 0) {
        my_putstr_err("./");
        my_putstr_err(data.command[command]);
        my_putstr_err(": Exec format error. Wrong Architecture.\n");
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