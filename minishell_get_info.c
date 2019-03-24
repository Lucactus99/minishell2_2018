/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_get_info
*/

#include "my.h"

int find_path(char **env, int j)
{
    for (; env[j + 1] != NULL; j++) {
        if (my_strncmp(env[j], "PATH", 4) == 0)
            return (j);
    }
    return (j);
}

char **put_path(struct data data, int command)
{
    int j = 0;

    if (data.env[0] != NULL && data.env[0] != 0) {
        j = find_path(data.env, j);
        if (data.env[j + 1] == NULL && my_strncmp(data.env[j], "PATH", 4)) {
            data.env[j + 1] = malloc(sizeof(char) * 40);
            j++;
        }
    } else
        data.env[0] = malloc(sizeof(char) * 40);
    for (int i = 0; i < data.nbr_args[command]; i++) {
        if (i == 0) {
            data.env[j] = my_strcpy(data.env[j], data.path[i]);
            data.env[j] = my_strcat(data.env[j], "=");
        } else
            data.env[j] = my_strcat(data.env[j], data.path[i]);
    }
    return (data.env);
}

char **modify_path(struct data data, int command)
{
    if (data.path[0] != NULL) {
        for (int i = 0; data.path[i + 1] != 0; i++) {
            data.path[i] = NULL;
            free(data.path[i]);
        }
    }
    for (int i = 0; i < data.nbr_args[command]; i++)
        data.path[i] = malloc(sizeof(char) * 20);
    for (int i = 0; i < data.nbr_args[command]; i++)
        data.path[i] = my_strcpy(data.path[i], data.args[command][i + 1]);
    data.path[data.nbr_args[command]] = NULL;
    data.env = put_path(data, command);
    return (data.path);
}

char **fill_path(char **path, char **env, int i)
{
    int a = 0;
    int b = 0;

    for (int j = 5; env[i][j] != 0; j++) {
        if (env[i][j] == ':') {
            a++;
            b = 0;
        } else {
            path[a][b] = env[i][j];
            b++;
        }
    }
    path[a + 1] = NULL;
    return (path);
}

char **get_path(char **env)
{
    char **path;
    int i = 0;

    for (i = 0; my_strncmp(env[i], "PATH", 4) != 0; i++) {
        if (env[i + 1] == NULL && my_strncmp(env[i], "PATH", 4) != 0)
            return (NULL);
    }
    path = malloc(sizeof(char *) * count_lines(env[i]));
    for (int j = 0; j < count_lines(env[i]); j++)
        path[j] = malloc(sizeof(char) * 20);
    return (fill_path(path, env, i));
}