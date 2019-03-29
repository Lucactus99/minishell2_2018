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

void do_command_3(struct data data)
{
    int status;
    int i;
    int pipes[4];
    int out = open_type(data.redirection, data.redirection_name);

    if (out < 0)
        exit(84);
    pipe(pipes);
    pipe(pipes + 2);
    if (fork() == 0) {
        dup2(pipes[1], 1);
        close(pipes[0]);
        close(pipes[1]);
        close(pipes[2]);
        close(pipes[3]);
        execve(data.command[0], data.args[0], data.env);
    } else {
        if (fork() == 0) {
            dup2(pipes[0], 0);
            dup2(pipes[3], 1);
            close(pipes[0]);
            close(pipes[1]);
            close(pipes[2]);
            close(pipes[3]);
            execve(data.command[1], data.args[1], data.env);
        } else {
            if (fork() == 0) {
                dup2(pipes[2], 0);
                if (data.redirection != 0)
                    dup2(out, 1);
                close(pipes[0]);
                close(pipes[1]);
                close(pipes[2]);
                close(pipes[3]);
                execve(data.command[2], data.args[2], data.env);
            }
        }
    }
    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);
    for (i = 0; i < 3; i++)
        wait(&status);
}

void do_command_2(struct data data)
{
    int status;
    int i;
    int pipes[2];
    int out = open_type(data.redirection, data.redirection_name);

    if (out < 0)
        exit(84);
    pipe(pipes);
    if (fork() == 0) {
        dup2(pipes[1], 1);
        close(pipes[0]);
        close(pipes[1]);
        execve(data.command[0], data.args[0], data.env);
    } else {
        if (fork() == 0) {
            dup2(pipes[0], 0);
            if (data.redirection != 0)
                dup2(out, 1);
            close(pipes[0]);
            close(pipes[1]);
            execve(data.command[1], data.args[1], data.env);
        }
    }
    close(pipes[0]);
    close(pipes[1]);
    for (i = 0; i < 2; i++)
        wait(&status);
}

int do_command(struct data data)
{
    int status;
    int out = open_type(data.redirection, data.redirection_name);

    if (out < 0 && data.redirection != 0)
        exit(84);
    if (fork() == 0 && data.path[0] != NULL) {
        for (int i = 0; i < data.nbr_command; i++) {
            if (my_strncmp(data.command[i], "./", 2) == 0)
                do_binary(data, i);
        }
        if (data.nbr_command == 1) {
            if (data.redirection != 0)
                dup2(out, 1);
            if (execve(data.command[0], data.args[0], data.env) <= 0) {
                my_putstr_err(data.command[0]);
                my_putstr_err(": Permission denied.\n");
            }
        } else if (data.nbr_command == 2)
            do_command_2(data);
        else
            do_command_3(data);
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

int find_command_2(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        if (my_strcmp(data.command[i], "setenv") == 0) {
            ok = 1;
            data.exit_status = setenv_command(data, i);
        } else if (my_strcmp(data.command[i], "unsetenv") == 0) {
            data.exit_status = unsetenv_command(data, i);
            ok = 1;
        } else {
            if (is_existing(data, data.command[i]) == NULL) {
                my_putstr_err(data.command[i]);
                my_putstr_err(": Command not found.\n");
                data.exit_status = 1;
                ok = 1;
            } else
                data.command[i] = is_existing(data, data.command[i]);
        }
    }
    if (ok != 1)
        data.exit_status = do_command(data);
    return (data.exit_status);
}

int find_command(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        if (my_strcmp(data.command[i], "exit") == 0) {
            if (isatty(0))
                my_putstr("exit\n");
            while (1)
                exit(0);
        } else {
            if (my_strcmp(data.command[i], "cd") == 0)
                data.exit_status = cd_command(data, i);
            else if (my_strcmp(data.command[i], "env") == 0) {
                print_env(data.env);
                data.exit_status = 0;
            }
            else
                ok = 1;
        }
    }
    if (ok == 1)
        data.exit_status = find_command_2(data);
    return (data.exit_status);
}