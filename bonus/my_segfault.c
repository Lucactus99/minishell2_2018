/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_segfault
*/

int main(void)
{
    char *segv;

    segv[10] = 'z';
    return (0);
}