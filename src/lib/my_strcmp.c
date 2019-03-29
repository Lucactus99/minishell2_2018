/*
** EPITECH PROJECT, 2018
** d
** File description:
** d
*/

#include "my.h"

int compare_variable(char const *s1, char const *s2, int i)
{
    if (s1[i] < s2[i]) {
        return (-1);
    } else if (s1[i] > s2[i]) {
        return (1);
    } else {
        return (0);
    }
}

int my_strcmp(char const *s1, char const *s2)
{
    int i;

    if (s1 == NULL || s2 == NULL)
        return (-1);
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            return (compare_variable(s1, s2, i));
        }
    }
    if (s1[i] == '\0' && s2[i] != '\0') {
        return (-1);
    } else if (s1[i] != '\0' && s2[i] == '\0') {
        return (1);
    }
    return (0);
}
