/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** main
*/

#include "my.h"

static int main_loop(struct data data)
{
    char *str = "lucas";

    while (str != NULL && my_strcmp(str, "exit") != 0) {
        if (isatty(0))
            my_putstr("§> ");
        str = get_next_line(0);
        if (str != NULL && str[0] != 0)
            data = manage_user_input(data, str);
    }
    return (data.exit_status);
}

static char **new_path_to_env(char **env)
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
    return (main_loop(data));
}