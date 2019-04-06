/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_commands
*/

#include "my.h"

int count_commands(char *str)
{
    int counter = 1;
    int neighbor = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            if (check_error_pipe(str, i) == 84)
                return (84);
            counter++;
            neighbor++;
        }
        else {
            if (neighbor == 3)
                return (84);
            else
                neighbor = 0;
        }
    }
    return (counter);
}

static int get_length_one(char *str, int i)
{
    int length = 0;

    for (; str[i] != '|' && str[i] != '\0'; i++)
        length++;
    return (++length);
}

static char **loop_tab_command(struct data data, int *a, int *b, char *str)
{
    int i = 0;

    for (; str[i] != '\0' && str[i] != '>' && str[i] != '<'; i++) {
        if (str[i + 1] == '|') {
            data.command[a[0]][b[0]] = '\0';
            a[0]++;
            i += 2;
            b[0] = 0;
            data.command[a[0]] = malloc(sizeof(char) * get_length_one(str, i));
        } else {
            data.command[a[0]][b[0]] = str[i];
            b[0]++;
        }
    }
    if (str[i] == '>' || str[i] == '<') {
        if (data.command[a[0]][b[0] - 1] == ' ')
            b[0]--;
    }
    return (data.command);
}

char **get_tab_command(struct data data, char *str)
{
    int a = 0;
    int b = 0;

    data.command[a] = malloc(sizeof(char) * get_length_one(str, 0));
    data.command = loop_tab_command(data, &a, &b, str);
    data.command[a][b] = '\0';
    data.command[a + 1] = NULL;
    return (data.command);
}

static int check_next_command(char *str, int nbr)
{
    for (int i = nbr; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != ';')
            return (nbr + 1);
    }
    return (84);
}

char *get_actual_command_line(char *str)
{
    char *actual = NULL;
    static int i = 0;
    int a = 0;

    if (str == NULL || str[i] == '\0' || i == 84) {
        i = 0;
        return (NULL);
    } else
        actual = malloc(sizeof(char) * (my_strlen(str) + 1));
    for (; str[i] != '\0' && str[i] != ';'; i++) {
        actual[a] = str[i];
        a++;
    }
    if (str[i] != '\0')
        i = check_next_command(str, i);
    actual[a] = '\0';
    return (actual);
}