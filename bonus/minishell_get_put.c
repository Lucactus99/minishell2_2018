/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_get_put
*/

#include "my.h"

char **put_old_pwd(char **env, char *pwd)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "OLDPWD", 6) == 0) {
            env[i] = malloc(sizeof(char) * (my_strlen(pwd) + 7));
            env[i] = my_strcpy(env[i], "OLDPWD=");
            env[i] = my_strcat(env[i], pwd);
            return (env);
        }
    }
    return (env);
}

char *get_old_pwd(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i] != 0; i++) {
        if (my_strncmp(env[i], "OLDPWD=", 7) == 0) {
            str = malloc(sizeof(char) * my_strlen(env[i]));
            str = my_strcpy(str, env[i]);
        }
    }
    if (str == NULL)
        return (NULL);
    for (int i = 0; i < 7; i++)
        str++;
    return (str);
}

char *get_home(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "HOME", 4) == 0) {
            str = malloc(sizeof(char) * my_strlen(env[i]));
            str = my_strcpy(str, env[i]);
        }
    }
    if (str == NULL)
        return (NULL);
    while (str[0] != '=')
        str++;
    str++;
    return (str);
}

char *get_program_name(char *av)
{
    char *str;
    int i = 0;
    int j = 0;

    for (; av[i] != ' ' && av[i] != '\0'; i++);
    str = malloc(sizeof(char) * (i + 1));
    for (; j < i; j++)
        str[j] = av[j];
    str[j] = '\0';
    return (str);
}

int get_nbr_args(char *av)
{
    int count = 0;

    for (int i = 0; av[i] != 0; i++) {
        if (av[i] == ' ')
            count++;
    }
    return (count);
}