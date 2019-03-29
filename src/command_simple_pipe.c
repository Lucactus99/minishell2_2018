/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** command_simple_pipe
*/

#include "my.h"

static void do_dup_simple_pipe(struct data data, int pipes[])
{
    int out = open_type(data.redirection, data.redirection_name);

    if (fork() == 0) {
        dup2(pipes[0], 0);
        if (data.redirection != 0)
            dup2(out, 1);
        close(pipes[0]);
        close(pipes[1]);
        execve(data.command[1], data.args[1], data.env);
    }
}

void do_command_simple_pipe(struct data data)
{
    int status;
    int i;
    int pipes[2];

    pipe(pipes);
    if (fork() == 0) {
        dup2(pipes[1], 1);
        close(pipes[0]);
        close(pipes[1]);
        execve(data.command[0], data.args[0], data.env);
    } else
        do_dup_simple_pipe(data, pipes);
    close(pipes[0]);
    close(pipes[1]);
    for (i = 0; i < 2; i++)
        wait(&status);
}