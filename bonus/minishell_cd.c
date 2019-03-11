/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_cd
*/

#include "my.h"

int cd_home_command(struct data data)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    data.env = put_old_pwd(data.env, pwd);
    if (chdir(get_home(data.env)) < 0) {
        if (errno == 14)
            my_putstr_err("cd: No home directory.\n");
        else if (errno == 20) {
            my_putstr_err(data.args[1]);
            my_putstr_err(": Not a directory.\n");
        } else
            my_putstr_err("cd: Can't change to home directory.\n");
        return (1);
    }
    return (0);
}

int cd_old_command(struct data data)
{
    char pwd[128];

    data.old_pwd = get_old_pwd(data.env);
    if (data.old_pwd == NULL) {
        my_putstr_err(": No such file or directory.\n");
        return (1);
    }
    getcwd(pwd, sizeof(pwd));
    if (chdir(data.old_pwd) < 0) {
        my_putstr_err(": No such file or directory.\n");
        return (1);
    }
    else
        data.env = put_old_pwd(data.env, pwd);
    return (0);
}

void print_cd_err(char *str)
{
    if (errno == 20) {
        my_putstr_err(str);
        my_putstr_err(": Not a directory.\n");
    } else if (errno == 2) {
        my_putstr_err(str);
        my_putstr_err(": No such file or directory.\n");
    }
}

int cd_command(struct data data)
{
    char pwd[128];

    if (data.args[1] == NULL || my_strcmp(data.args[1], "~") == 0)
        return (cd_home_command(data));
    else if (my_strcmp(data.args[1], "-") == 0)
        return (cd_old_command(data));
    else {
        getcwd(pwd, sizeof(pwd));
        if (my_strcmp(data.args[1], ".") != 0)
            data.env = put_old_pwd(data.env, pwd);
        if (chdir(data.args[1]) < 0) {
            print_cd_err(data.args[1]);
            return (1);
        }
    }
    return (0);
}

void print_prompt(struct data data)
{
    char pwd[128];

    if (isatty(0)) {
        getcwd(pwd, sizeof(pwd));
        my_putstr("\033[1;36m");
        my_putstr(pwd);
        if (data.exit_status == 0) {
            my_putstr("\033[0m ");
            my_putstr("\033[1;32m§> \033[0m");
        } else {
            my_putstr("\033[0m ");
            my_putstr("\033[1;31m§> \033[0m");
        }
    }
}