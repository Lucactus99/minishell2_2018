/*
** EPITECH PROJECT, 2019
** transform_2d
** File description:
** transform_2d
*/

#include <stdlib.h>

static int count_lines(char *str, char sep)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == sep) && str[i + 1] != '\0')
            count++;
    }
    return (count);
}

char **transform_2d(char *str, char sep)
{
    char **str_2d = malloc(sizeof(char *) * (count_lines(str, sep) + 2));
    int j = 0;
    int k = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == sep) {
            str[i++] = '\0';
            str_2d[j] = &str[k];
            j++;
            k = i;
        }
    }
    str[i++] = '\0';
    str_2d[j] = &str[k];
    j++;
    k = i;
    str_2d[j] = NULL;
    return (str_2d);
}