/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** command_double_pipes
*/

#include "my.h"

static void close_pipes(int pipes[])
{
    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);
}

static void do_dup_double_pipes(struct data data, int pipes[])
{
    int out = open_type(data.redirection, data.redirection_name);

    if (fork() == 0) {
        dup2(pipes[0], 0);
        dup2(pipes[3], 1);
        close_pipes(pipes);
        execve(data.command[1], data.args[1], data.env);
    } else {
        if (fork() == 0) {
            dup2(pipes[2], 0);
            if (data.redirection != 0)
                dup2(out, 1);
            close_pipes(pipes);
            execve(data.command[2], data.args[2], data.env);
        }
    }
}

void do_command_double_pipes(struct data data)
{
    int status;
    int i;
    int pipes[4];

    pipe(pipes);
    pipe(pipes + 2);
    if (fork() == 0) {
        dup2(pipes[1], 1);
        close_pipes(pipes);
        execve(data.command[0], data.args[0], data.env);
    } else
        do_dup_double_pipes(data, pipes);
    close_pipes(pipes);
    for (i = 0; i < 3; i++)
        wait(&status);
}
