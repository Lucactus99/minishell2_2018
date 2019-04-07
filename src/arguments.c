/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** arguments
*/

#include "my.h"

static int check_pipe(char c, int redirection, int *pipe)
{
    if (c == '|') {
        if (redirection > pipe[0])
            return (1);
        pipe[0]++;
    }
    return (0);
}

int pipe_after_redirection(char *str)
{
    int pipe = 0;
    int redirection = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (check_pipe(str[i], redirection, &pipe) == 1)
            return (1);
        if (str[i] == '>' || str[i] == '<')
            redirection = pipe + 1;
    }
    return (0);
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

char **add_args(char **args, char *argument)
{
    int i = 0;

    for (; args[i] != NULL; i++);
    args[i] = malloc(sizeof(char *) * my_strlen(argument));
    args[i] = my_strcpy(args[i], argument);
    args[i + 1] = NULL;
    return (args);
}

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