/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_main
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

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            if (check_error_pipe(str, i) == 84)
                return (84);
            counter++;
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

char *get_actual_command_line(char *str)
{
    char *actual = malloc(sizeof(char) * my_strlen(str));
    static int i = 0;
    int a = 0;

    if (str[i] == '\0') {
        i = 0;
        return (NULL);
    }
    for (; str[i] != '\0' && str[i] != ';'; i++) {
        actual[a] = str[i];
        a++;
    }
    if (str[i] != '\0')
        i++;
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

    for (; actual[i] != '>' && actual[i] != '<'; i++);
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

char *is_ambiguous(char *str)
{
    int pipe = 0;
    int redirection = 100;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|')
            pipe++;
        else if (str[i] == '>' || str[i] == '<') {
            if (pipe < redirection)
                redirection = pipe;
        }
        if (pipe > redirection)
            return (NULL);
    }
    return (str);
}

int main_loop(struct data data)
{
    char *str = "lucas";
    int ok = 0;
    char *actual = NULL;

    while (str != NULL && my_strcmp(str, "exit") != 0) {
        if (isatty(0))
            my_putstr("§> ");
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            actual = get_actual_command_line(str);
            while (actual != NULL) {
                actual = remove_useless(actual);
                data.nbr_command = count_commands(actual);
                data.redirection = is_redirection(actual);
                if (data.nbr_command == 84)
                    my_putstr_err("Invalid null command.\n");
                else {
                    data.command = malloc(sizeof(char *) * data.nbr_command);
                    data.command = get_tab_command(data, actual);
                    if (data.redirection >= 1 && data.redirection <= 4) {
                        data.redirection_name = get_redirection_name(actual);
                        if (is_ambiguous(actual) == NULL) {
                            my_putstr_err("Ambiguous output redirect.\n");
                            data.redirection_name = is_ambiguous(actual);
                        }
                    }
                    if (data.redirection_name != NULL || data.redirection == 0) {
                        data.nbr_args = malloc(sizeof(int) * data.nbr_command);
                        for (int i = 0; i < data.nbr_command; i++)
                            data.nbr_args[i] = get_nbr_args(data.command[i]);
                        data.args = put_args(data.command, data.nbr_args, data.nbr_command);
                        if (data.redirection == 3) {
                            data.command[data.nbr_command - 1] = my_strcat(data.command[data.nbr_command - 1], " ");
                            data.nbr_args[data.nbr_command - 1] = get_nbr_args(my_strcat(data.command[data.nbr_command - 1], get_buffer(data.redirection_name))) + 1;
                            data.args[data.nbr_command - 1] = transform_2d(get_buffer(data.redirection_name));
                        }
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