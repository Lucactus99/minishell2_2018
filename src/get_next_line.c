/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

static char *my_strcat(char *str1, char *str2)
{
    int length1;
    int length2;
    char *result;
    int a = 0;

    if (str2 == NULL)
        return (str1);
    if (str1 == NULL)
        return (str2);
    length1 = my_strlen(str1);
    length2 = my_strlen(str2);
    result = malloc(sizeof(char) * (length1 + length2 + 1));
    if (result == NULL)
        return (NULL);
    for (int i = 0; str1[i] != 0; i++)
        result[a++] = str1[i];
    for (int i = 0; str2[i] != 0; i++)
        result[a++] = str2[i];
    result[a] = 0;
    return (result);
}

static void alloc_buffer(const int fd, char **buffer)
{
    int i;

    *buffer = malloc(sizeof(char) * (READ_SIZE + 1));
    if (*buffer == NULL)
        return;
    i = read(fd, *buffer, READ_SIZE);
    if (i < 0)
        return;
    (*buffer)[i] = 0;
}

static int put_in_str(char **buffer, char **str)
{
    int i = 0;

    *str = malloc(sizeof(char) * (READ_SIZE + 1));
    if (*str == NULL)
        return (-1);
    while (**buffer != 0 && (*(*buffer - 1) != '\n' || i == 0)) {
        str[0][i] = **buffer;
        (*buffer)++;
        i++;
    }
    return (i);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *str;
    int i;

    if (fd < 0)
        return (NULL);
    if (buffer == NULL || buffer[0] == 0)
        alloc_buffer(fd, &buffer);
    if (buffer == NULL || buffer[0] == 0)
        return (NULL);
    i = put_in_str(&buffer, &str);
    if (i < 0)
        return (NULL);
    str[i] = 0;
    if (i != 0 && str[i - 1] == '\n')
        str[i - 1] = 0;
    else
        str = my_strcat(str, get_next_line(fd));
    return (str);
}