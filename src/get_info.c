/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_info
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

int get_nbr_lines(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return (++i);
}

char **my_strdup_2d(char **tab)
{
    char **tmp = malloc(sizeof(char *) * get_nbr_lines(tab));
    int a = 0;

    for (int i = 0; tab[i] != NULL; i++)
        tmp[i] = malloc(sizeof(char) * (my_strlen(tab[i]) + 1));
    for (; tab[a] != NULL; a++) {
        tmp[a] = my_strcpy(tmp[a], tab[a]);
    }
    tmp[a] = NULL;
    return (tmp);
}

char **get_path(char **env)
{
    char **tmp_env = my_strdup_2d(env);
    char **path = NULL;
    int i = 0;

    for (i = 0; my_strncmp(tmp_env[i], "PATH=", 5) != 0; i++) {
        if (tmp_env[i + 1] == NULL && my_strncmp(tmp_env[i], "PATH=", 5) != 0)
            return (NULL);
    }
    path = transform_2d(&tmp_env[i][5], ':');
    return (path);
}