/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_env
*/

#include "my.h"

int setenv_command(struct data data)
{
    if (data.nbr_args == 0) {
        print_env(data.env);
        return (0);
    }
    if (data.nbr_args >= 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        return (1);
    }
    if (my_str_isalpha(data.args[1]) == 0) {
        my_putstr_err("setenv: Variable name must ");
        my_putstr_err("contain alphanumeric characters.\n");
        return (1);
    }
    if (my_strncmp(data.args[1], "PATH", 4) == 0)
        data.path = modify_path(data);
    else
        data.env = set_env(data);
    return (0);
}

int unsetenv_command(struct data data)
{
    if (data.args[1] == NULL) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        return (1);
    } else
        data.env = unset_env(data);
    return (0);
}

char **set_env(struct data data)
{
    int i = 0;
    int length = find_line_env(data);

    if (length >= 0) {
        for (; data.env[length][i] != '='; i++);
        i++;
        for (int j = i; data.env[length][j + 1] != 0; j++)
            data.env[length][j] = 0;
        for (int j = 2; j <= data.nbr_args; j++)
            data.env[length] = my_strcat(data.env[length], data.args[j]);
    } else
        data.env = add_env(data);
    return (data.env);
}

char **unset_env(struct data data)
{
    int j = 0;
    int length = find_line_env(data);

    if (length >= 0) {
        data.env[length] = NULL;
        for (j = length; data.env[j + 1] != 0; j++)
            data.env[j] = data.env[j + 1];
        data.env[j] = 0;
    }
    return (data.env);
}

void print_env(char **env)
{
    for (int i = 0; env[i] != 0; i++) {
        my_putstr(env[i]);
        my_putchar('\n');
    }
}