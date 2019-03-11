/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_putstr_err
*/

#include "my.h"

int my_putstr_err(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar_err(str[i]);
    }
    return (0);
}
