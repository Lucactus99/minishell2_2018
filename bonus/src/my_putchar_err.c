/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_putchar_err
*/

#include <unistd.h>

void my_putchar_err(char c)
{
    write(2, &c, 1);
}
