/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** arguments
*/

#include "my.h"

// static char ***malloc_tab_3d(int *nbr_args, int nbr_command)
// {
//     char ***tmp = malloc(sizeof(char **) * nbr_command);

//     for (int i = 0; i < nbr_command; i++) {
//         tmp[i] = malloc(sizeof(char *) * (nbr_args[i] + 1));
//         for (int j = 0; j <= nbr_args[i] + 1; j++)
//             tmp[i][j] = malloc(sizeof(char) * 20);
//     }
//     return (tmp);
// }

char ***put_args(char **av, int *nbr_args, int nbr_command)
{
    int j = 0;
    int k = 0;
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