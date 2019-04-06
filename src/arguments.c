/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** arguments
*/

#include "my.h"

char ***put_args(char **av, int nbr_command)
{
    char ***tmp = malloc(sizeof(char **) * nbr_command);

    for (int h = 0; av[h] != NULL; h++) {
        tmp[h] = transform_2d(av[h], ' ');
        if (tmp[h][0] == NULL) {
            tmp[h][0] = malloc(sizeof(char) * (my_strlen(av[h]) + 1));
            tmp[h][0] = my_strcpy(tmp[h][0], av[h]);
        }
    }
    return (tmp);
}