/*
** EPITECH PROJECT, 2018
** my_strncmp.c
** File description:
** d
*/

#include "my.h"

int check_number(char const *s1, char const *s2, int n)
{
    for (int i = 0; i < n; i++) {
        if (s1[i] == '\0' || s2[i] == '\0')
            return (i);
        if (s1[i] != s2[i])
            return (i);
    }
    return (n - 1);
}

int check_length(char const *s1, char const *s2, int nb, int n)
{
    if (my_strlen(s1) < nb) {
        if (s1[nb] != 0)
            return (s1[nb]);
        else
            return (s1[n + 1]);
    }
    else if (my_strlen(s2) < nb) {
        if (s2[nb] != 0)
            return (s2[nb]);
        else
            return (s2[n + 1]);
    }
    return (0);
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    n = check_number(s1, s2, n);
    if ((s1[n] - s2[n]) == 0)
        return (0);
    return (s1[n] - s2[n]);
}
