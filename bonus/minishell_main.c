/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_main
*/

#include "my.h"

int do_binary(struct data data)
{
    data.program_name += 2;
    if (execve(data.program_name, data.args, data.env) <= 0) {
        if (errno == 8) {
            my_putstr_err("./");
            my_putstr_err(data.program_name);
            my_putstr_err(": Exec format error. Binary file not executable.\n");
        } else if (errno == 2) {
            my_putstr_err("./");
            my_putstr_err(data.program_name);
            my_putstr_err(": Command not found.\n");
        }
    }
    exit(1);
}

char *const *put_args(char *av, int nbr_args)
{
    char **tmp = malloc(sizeof(char *) * (nbr_args + 1));
    int j = 0;
    int k = 0;

    for (int i = 0; i <= nbr_args + 1; i++)
        tmp[i] = malloc(sizeof(char) * 20);
    for (int i = 0; av[i] != '\0'; i++) {
        if (av[i] == ' ') {
            j++;
            k = 0;
        } else {
            tmp[j][k] = av[i];
            k++;
        }
    }
    tmp[j + 1][0] = '\0';
    tmp[j + 1] = NULL;
    return (tmp);
}

int main_loop(struct data data)
{
    char *str = "lucas";

    while (str != NULL && my_strcmp(str, "exit") != 0) {
        print_prompt(data);
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            str = remove_useless(str);
            data.program_name = get_program_name(str);
            data.nbr_args = get_nbr_args(str);
            data.args = put_args(str, data.nbr_args);
            data.exit_status = find_command(data);
            free_command(data, str);
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
