/*
** EPITECH PROJECT, 2018
** h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_
#define GNU_SOURCE

#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


struct data
{
    char *program_name;
    int *nbr_args;
    char ***args;
    char **path;
    char *old_pwd;
    char **env;
    int exit_status;
    char **command;
    int nbr_command;
    int redirection;
    char *redirection_name;
};

// LIB
void my_putchar(char);
int my_putstr(char const *);
int my_strlen(char const *);
int my_put_nbr(int);
char *my_strcpy(char *, char const *);
char *get_next_line(int);
int my_strcmp(char const *, char const *);
char *my_strcat(char *, char const *);
int my_strncmp(char const *, char const *, int);
void my_putchar_err(char);
int my_putstr_err(char const *);
int my_str_isalpha(char const *);
char **transform_2d(char *str);

// USEFUL
void free_command(struct data, char *);
int count_lines(char *);
char **get_path(char **);
char *get_program_name(char *);
int get_nbr_args(char *);
int kill(pid_t pid, int sig);
char *is_existing(struct data, char *);
char *remove_useless(char *);
void print_error(int);
void print_error_5(int);

// COMMANDS
int do_command(struct data);
int find_command(struct data);
int do_binary(struct data, int);

// ENV
void print_env(char **);
char **add_env(struct data, int);
int find_line_env(struct data, int);
char **set_env(struct data, int);
char **unset_env(struct data, int);
int setenv_command(struct data, int);
int unsetenv_command(struct data, int);

// PATH
char **modify_path(struct data, int);
char **put_path(struct data, int);
char **rm_path(struct data);

// BUILTIN
char *get_home(char **);
char *get_old_pwd(char **);
char **put_old_pwd(char **, char *);
int cd_command(struct data, int);

#endif //MY_H_