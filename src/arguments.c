/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** arguments
*/

#include "my.h"

static char ***malloc_tab_3d(int *nbr_args, int nbr_command)
{
    char ***tmp = malloc(sizeof(char **) * nbr_command);

    for (int i = 0; i < nbr_command; i++) {
        tmp[i] = malloc(sizeof(char *) * (nbr_args[i] + 1));
        for (int j = 0; j <= nbr_args[i] + 1; j++)
            tmp[i][j] = malloc(sizeof(char) * 20);
    }
    return (tmp);
}

char ***put_args(char **av, int *nbr_args, int nbr_command)
{
    int j = 0;
    int k = 0;
    char ***tmp = malloc_tab_3d(nbr_args, nbr_command);

    for (int h = 0; av[h] != NULL; h++) {
        for (int i = 0; av[h][i] != '\0'; i++) {
            if (av[h][i] == ' ') {
                j++;
                k = 0;
            } else {
                tmp[h][j][k] = av[h][i];
                k++;
            }
        }
        tmp[h][j + 1][0] = '\0';
        tmp[h][j + 1] = NULL;
        j = 0;
        k = 0;
    }
    return (tmp);
}