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

static void alloc_buffer(const int fd, char *buffer)
{
    int i;

    for (size_t j = 0; j < READ_SIZE; j++)
        buffer[j] = '\0';
    i = read(fd, buffer, READ_SIZE);
    if (i < 0)
        return;
    buffer[i] = '\0';
}

static int put_in_str(char *buffer, char **ptr)
{
    int i = 0;
    size_t j = 0;
    size_t idx = 0;
    char *str = malloc(sizeof(char) * (READ_SIZE + 2));

    if (str == NULL)
        return (-1);
    while (buffer[idx] && (!idx || buffer[idx - 1] != '\n')) {
        str[i++] = buffer[idx++];
    }
    str[i] = '\0';
    *ptr = str;
    for (; buffer[idx]; ++j) {
        buffer[j] = buffer[idx++];        
    }
    buffer[j] = '\0';
    return (i);
}

char *get_next_line(int fd)
{
    static char buffer[READ_SIZE + 1] = {0};
    char *str = NULL;
    int i;

    if (fd < 0 || READ_SIZE <= 0)
        return (NULL);
    if (buffer == NULL || buffer[0] == 0)
        alloc_buffer(fd, buffer);
    if (buffer == NULL || buffer[0] == 0)
        return (NULL);
    i = put_in_str(buffer, &str);
    if (i < 0)
        return (NULL);
    if (i != 0 && str[i - 1] == '\n')
        str[i - 1] = '\0';
    else
        str = my_strcat(str, get_next_line(fd));
    return (str);
}