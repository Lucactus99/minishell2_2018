/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_useful
*/

#include "my.h"

void free_command(struct data data, char *str)
{
    free(data.program_name);
    free(str);
    for (int i = 1; i < data.nbr_args; i++)
        free(data.args[i]);
}

int count_lines(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == ':')
            count++;
    }
    count++;
    return (count);
}

int find_line_env(struct data data)
{
    int line = -1;
    char *str = malloc(sizeof(char) * (my_strlen(data.args[1]) + 2));

    str = my_strcpy(str, data.args[1]);
    str[my_strlen(str)] = '=';
    str[my_strlen(str) + 1] = 0;
    for (int i = 0; data.env[i] != 0; i++) {
        if (my_strncmp(data.env[i], str, my_strlen(str)) == 0)
            line = i;
    }
    return (line);
}

int check_error_path(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '/' && (str[i + 1] == '/' || str[i + 1] == '\0'))
            return (1);
    }
    return (0);
}

char *is_existing(struct data data)
{
    char *tmp;
    char *binary = "binary";

    if (my_strncmp(data.program_name, "./", 2) == 0)
        return (binary);
    if (access(data.program_name, F_OK) == 0) {
        tmp = malloc(sizeof(char) * my_strlen(data.program_name) + 1);
        tmp = my_strcpy(tmp, data.program_name);
        return (tmp);
    }
    for (int i = 0; data.path[i] != NULL && data.path[i][0] != 0; i++) {
        tmp = malloc(sizeof(char) * 40);
        tmp = my_strcpy(tmp, data.path[i]);
        tmp = my_strcat(tmp, "/");
        tmp = my_strcat(tmp, data.program_name);
        if (access(tmp, F_OK) == 0 && check_error_path(tmp) == 0)
            return (tmp);
        free(tmp);
    }
    return (NULL);
}