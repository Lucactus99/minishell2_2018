/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** env
*/

#include "my.h"

char **set_env(struct data data, int command)
{
    int i = 0;
    int length = find_line_env(data, command);

    if (length >= 0) {
        for (; data.env[length][i] != '='; i++);
        i++;
        for (int j = i; data.env[length][j + 1] != 0; j++)
            data.env[length][j] = 0;
        for (int j = 2; j <= data.nbr_args[command]; j++) {
            data.env[length] = my_strcat(data.env[length],
            data.args[command][j]);
        }
    } else
        data.env = add_env(data, command);
    return (data.env);
}

char **unset_env(struct data data, int command)
{
    int j = 0;
    int length = find_line_env(data, command);

    if (length >= 0) {
        data.env[length] = NULL;
        for (j = length; data.env[j + 1] != 0; j++)
            data.env[j] = data.env[j + 1];
        data.env[j] = 0;
    }
    return (data.env);
}

int setenv_command(struct data data, int command)
{
    if (data.nbr_args[command] == 0) {
        print_env(data.env);
        return (0);
    }
    if (data.nbr_args[command] >= 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        return (1);
    }
    if (my_str_isalpha(data.args[command][1]) == 0) {
        my_putstr_err("setenv: Variable name must ");
        my_putstr_err("contain alphanumeric characters.\n");
        return (1);
    }
    if (my_strncmp(data.args[command][1], "PATH", 4) == 0)
        data.path = modify_path(data, command);
    else
        data.env = set_env(data, command);
    return (0);
}

int unsetenv_command(struct data data, int command)
{
    if (data.args[command][1] == NULL) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        return (1);
    } else
        data.env = unset_env(data, command);
    return (0);
}

void do_pipe(struct data data, int i)
{
    int pipes[2];
    int out = open_type(data.redirection, data.redirection_name);
    static int fd_in = 0;

    pipe(pipes);
    if (fork() == 0) {
        dup2(fd_in, 0);
        if (data.command[i + 1] != NULL)
            dup2(pipes[1], 1);
        else {
            if (data.redirection != 0) 
                dup2(out, 1);
        }
        close(pipes[0]);
        if (my_strcmp(data.command[i], "setenv") == 0)
            print_env(data.env);
        else if (my_strncmp(data.command[i], "./", 2) == 0) {
            do_binary(data, i);
        }
        else {
            if (execve(data.command[i], data.args[i], data.env) < 0) {
                my_putstr_err(data.command[0]);
                my_putstr_err(": Permission denied.\n");
            }
        }
        exit(0);
    } else {
        wait(NULL);
        close(pipes[1]);
        fd_in = pipes[0];
        if (data.command[i + 1] == NULL) {
            close(out);
            close(pipes[0]);
            close(fd_in);
        }
        exit(0);
    }
}

void print_env(char **env)
{
    for (int i = 0; env[i] != 0; i++) {
        my_putstr(env[i]);
        my_putchar('\n');
    }
}