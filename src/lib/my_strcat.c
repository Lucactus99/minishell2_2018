/*
** EPITECH PROJECT, 2018
** d
** File description:
** d
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int length_dest = my_strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; i++) {
        dest[length_dest + i] = src[i];
    }
    dest[length_dest + i] = '\0';
    return (dest);
}
