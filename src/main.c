/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** main
*/

#include "my.h"

int do_binary(struct data data, int command)
{
    data.command[command] += 2;
    if (execve(data.command[command], data.args[command], data.env) <= 0) {
        if (errno == 8) {
            my_putstr_err("./");
            my_putstr_err(data.command[command]);
            my_putstr_err(": Exec format error. Wrong Architecture.\n");
        } else if (errno == 2) {
            my_putstr_err("./");
            my_putstr_err(data.command[command]);
            my_putstr_err(": Command not found.\n");
        } else {
            my_putstr_err("./");
            my_putstr_err(data.command[command]);
            my_putstr_err(": Permission denied.\n");
        }
    }
    exit(1);
}

char ***put_args(char **av, int *nbr_args, int nbr_command)
{
    char ***tmp = malloc(sizeof(char **) * nbr_command);
    int j = 0;
    int k = 0;

    for (int i = 0; i < nbr_command; i++) {
        tmp[i] = malloc(sizeof(char *) * (nbr_args[i] + 1));
        for (int j = 0; j <= nbr_args[i] + 1; j++)
            tmp[i][j] = malloc(sizeof(char) * 20);
    }
    for (int h = 0; av[h] != NULL; h++) {
        for (int i = 0; av[h][i] != '\0'; i++) {
            if (av[h][i] == ' ') {
                j++;
                k = 0;
            } else {
                tmp[h][j][k] = av[h][i];
                k++;
            }
        }
        tmp[h][j + 1][0] = '\0';
        tmp[h][j + 1] = NULL;
        j = 0;
        k = 0;
    }
    return (tmp);
}

int check_error_pipe(char *str, int i)
{
    for (; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '|')
            return (0);
    }
    return (84);
}

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

int get_length_one_command(char *str, int i)
{
    int length = 0;

    for (int i = 0; str[i] != '|' && str[i] != '\0'; i++)
        length++;
    return (length);
}

char **get_tab_command(struct data data, char *str)
{
    int a = 0;
    int b = 0;
    data.command[a] = malloc(sizeof(char) * get_length_one_command(str, 0));

    for (int i = 0; str[i] != '\0' && str[i + 1] != '>' && str[i + 1] != '<'; i++) {
        if (str[i + 1] == '|') {
            data.command[a][b] = '\0';
            a++;
            i += 2;
            b = 0;
            data.command[a] = malloc(sizeof(char) * get_length_one_command(str, i));
        } else {
            data.command[a][b] = str[i];
            b++;
        }
    }
    data.command[a][b] = '\0';
    data.command[a + 1] = NULL;
    return (data.command);
}

int check_next_command(char *str, int nbr)
{
    for (int i = nbr; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != ';')
            return (nbr + 1);
    }
    return (84);
}

char *get_actual_command_line(char *str)
{
    char *actual;
    static int i = 0;
    int a = 0;

    if (str == NULL || i == 84) {
        i = 0;
        return (NULL);
    }
    else
        actual = malloc(sizeof(char) * my_strlen(str));
    if (str[i] == '\0') {
        i = 0;
        return (NULL);
    }
    for (; str[i] != '\0' && str[i] != ';'; i++) {
        actual[a] = str[i];
        a++;
    }
    if (str[i] != '\0') {
        i = check_next_command(str, i);
    }
    actual[a] = '\0';
    return (actual);
}

int is_redirection(char *actual)
{
    for (int i = 0; actual[i] != '\0'; i++) {
        if (actual[i] == '>') {
            if (actual[i + 1] == '>')
                return (2);
            return (1);
        }
        if (actual[i] == '<') {
            if (actual[i + 1] == '<')
                return (4);
            return (3);
        }
    }
    return (0);
}

char *get_redirection_name(char *actual)
{
    int i = 0;
    int a = 0;
    char *str = malloc(sizeof(char) * my_strlen(actual));

    for (; actual[i] != '>' && actual[i] != '<' && actual[i] != '\0'; i++);
    if ((actual[i] == '>' && actual[i + 1] == '<') || (actual[i] == '<' && actual[i + 1] == '>')) {
        my_putstr_err("Missing name for redirect.\n");
        return (NULL);
    }
    i++;
    if (actual[i] == '>' || actual[i] == '<')
        i++;
    if (actual[i] == '>' || actual[i] == '<') {
        my_putstr_err("Missing name for redirect.\n");
        return (NULL);
    }
    for (; actual[i] == ' '; i++);
    for (; actual[i] != '\0'; i++) {
        str[a] = actual[i];
        a++;
    }
    str[a] = '\0';
    if (my_strlen(str) <= 1) {
        my_putstr_err("Missing name for redirect.\n");
        return (NULL);
    }
    return (str);
}

char *get_buffer(char *filename)
{
    int out = open(filename, O_RDWR|O_CREAT|O_APPEND, 0600);
    char *buff = malloc(sizeof(char) * 20);
    int i = 0;

    read(out, buff, 20);
    for (; buff[i] > 20; i++);
    buff[i] = '\0';
    return (buff);
}

int count_redirections(char *str)
{
    int counter_left = 0;
    int counter_right = 0;

    for (int i = 0; str[i + 1] != '\0'; i++) {
        if (str[i] == '>' && str[i + 1] != '>')
            counter_right++;
        if (str[i] == '<' && str[i + 1] != '<')
            counter_left++;
    }
    if (counter_right > 1)
        return (1);
    if (counter_left > 1)
        return (2);
    if (counter_left + counter_right > 1) {
        if (counter_left > counter_right)
            return (2);
        else
            return (1);
    }
    if (str[my_strlen(str) - 1] == '>' || str[my_strlen(str) - 1] == '<')
        return (3);
    return (0);
}

char *is_ambiguous(char *str)
{
    if (count_redirections(str) == 1)
        return ("right");
    if (count_redirections(str) == 2)
        return ("left");
    if (count_redirections(str) == 3)
        return ("missing");
    return (str);
}

int main_loop(struct data data)
{
    char *str = "lucas";
    int ok = 0;
    char *actual = NULL;
    char *ambiguous = NULL;

    while (str != NULL && my_strcmp(str, "exit") != 0) {
        if (isatty(0))
            my_putstr("§> ");
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            actual = get_actual_command_line(str);
            if (count_commands(str) == 84) {
                my_putstr_err("Invalid null command.\n");
                actual = get_actual_command_line(str);
                actual = NULL;
                str = "lucas";
                data.exit_status = 1;
            }
            while (actual != NULL) {
                actual = remove_useless(actual);
                data.nbr_command = count_commands(actual);
                data.redirection = is_redirection(actual);
                if (data.nbr_command == 84) {
                    my_putstr_err("Invalid null command.\n");
                    str = "lucas";
                    data.exit_status = 1;
                } else {
                    data.command = malloc(sizeof(char *) * data.nbr_command);
                    data.command = get_tab_command(data, actual);
                    if (data.redirection == 1 || data.redirection == 2 || data.redirection == 3 || data.redirection == 4) {
                        data.redirection_name = get_redirection_name(actual);
                        ambiguous = is_ambiguous(actual);
                        if (my_strcmp("left", ambiguous) == 0) {
                            my_putstr_err("Ambiguous input redirect.\n");
                            data.redirection_name = NULL;
                            data.exit_status = 1;
                        }
                        if (my_strcmp("right", ambiguous) == 0) {
                            my_putstr_err("Ambiguous output redirect.\n");
                            data.redirection_name = NULL;
                            data.exit_status = 1;
                        }
                        if (my_strcmp("missing", ambiguous) == 0 && data.redirection_name != NULL) {
                            my_putstr_err("Missing name for redirect.\n");
                            data.redirection_name = NULL;
                            data.exit_status = 1;
                        }
                    }
                    if (data.redirection_name != NULL || data.redirection == 0) {
                        data.nbr_args = malloc(sizeof(int) * data.nbr_command);
                        for (int i = 0; i < data.nbr_command; i++)
                            data.nbr_args[i] = get_nbr_args(data.command[i]);
                        data.args = put_args(data.command, data.nbr_args, data.nbr_command);
                        for (int i = 0; i < data.nbr_command; i++)
                            data.command[i] = get_program_name(data.command[i]);
                        data.exit_status = find_command(data);
                        free_command(data, actual);
                    }
                }
                actual = get_actual_command_line(str);
            }
        }
    }
    return (data.exit_status);
}

char **new_path_to_env(char **env)
{
    int j = 0;

    for (; env[j] != NULL; j++);
    env[j] = malloc(sizeof(char) * 50);
    env[j] = my_strcpy(env[j],
    "PATH=/bin:/usr/local/bin:/sbin:/usr/bin:/usr/sbin");
    env[j + 1] = 0;
    return (env);
}

int main(int ac, char **av, char **env)
{
    struct data data;

    if (env == NULL)
        return (84);
    (void)ac;
    (void)av;
    data.exit_status = 0;
    data.redirection_name = NULL;
    if (env[0] == 0)
        env = new_path_to_env(env);
    data.path = get_path(env);
    if (data.path == NULL) {
        env = new_path_to_env(env);
        data.path = get_path(env);
    }
    data.env = env;
    data.exit_status = main_loop(data);
    return (data.exit_status);
}