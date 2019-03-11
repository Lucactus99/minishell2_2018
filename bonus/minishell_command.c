/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_command
*/

#include "my.h"

int do_command(struct data data, char *tmp)
{
    int c_pid = fork();
    int status;

    if (c_pid == 0 && data.path[0] != NULL) {
        if (my_strncmp(data.program_name, "./", 2) == 0)
            do_binary(data);
        if (execve(tmp, data.args, data.env) <= 0) {
            my_putstr_err(tmp);
            my_putstr_err(": Permission denied.\n");
        }
        exit(1);
    } else if (c_pid > 0)
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
    char *tmp;

    if (my_strcmp(data.program_name, "setenv") == 0) {
        data.exit_status = setenv_command(data);
    } else if (my_strcmp(data.program_name, "unsetenv") == 0) {
        data.exit_status = unsetenv_command(data);
    } else {
        tmp = is_existing(data);
        if (tmp != NULL) {
            data.exit_status = do_command(data, tmp);
        } else {
            my_putstr_err(data.program_name);
            my_putstr_err(": Command not found.\n");
            data.exit_status = 1;
        }
    }
    return (data.exit_status);
}

int find_command(struct data data)
{
    if (my_strcmp(data.program_name, "exit") == 0) {
        if (isatty(0))
            my_putstr("exit\n");
        while (1)
            exit(0);
    } else {
        if (my_strcmp(data.program_name, "cd") == 0)
            data.exit_status = cd_command(data);
        else if (my_strcmp(data.program_name, "env") == 0)
            print_env(data.env);
        else
            data.exit_status = find_command_2(data);
    }
    return (data.exit_status);
}