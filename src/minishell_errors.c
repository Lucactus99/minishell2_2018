/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** minishell_options
*/

#include "my.h"

void print_error_4(int status)
{
    if (WTERMSIG(status) == 25)
        my_putstr_err("Filesize limit exceeded\n");
    if (WTERMSIG(status) == 26)
        my_putstr_err("Virtual time alarm\n");
    if (WTERMSIG(status) == 27)
        my_putstr_err("Profiling time alarm\n");
    if (WTERMSIG(status) == 29)
        my_putstr_err("Pollable event occured\n");
    if (WTERMSIG(status) == 30)
        my_putstr_err("Power failure\n");
    if (WTERMSIG(status) == 31)
        my_putstr_err("Bad system call\n");
    if (WTERMSIG(status) == 32)
        my_putstr_err("Signal 32\n");
    if (WTERMSIG(status) == 33)
        my_putstr_err("Signal 33\n");
    if (WTERMSIG(status) == 34)
        my_putstr_err("First Realtime Signal\n");
    print_error_5(status);
}

void print_error_3(int status)
{
    if (WTERMSIG(status) == 11) {
        my_putstr_err("Segmentation fault");
        if (__WCOREDUMP(status) != 0)
            my_putstr_err(" (core dumped)\n");
        else
            my_putchar('\n');
    }
    if (WTERMSIG(status) == 12)
        my_putstr_err("User signal 2\n");
    if (WTERMSIG(status) == 13)
        my_putstr_err("Broken pipe\n");
    if (WTERMSIG(status) == 14)
        my_putstr_err("Alarm clock\n");
    if (WTERMSIG(status) == 15)
        my_putstr_err("Terminated\n");
    if (WTERMSIG(status) == 16)
        my_putstr_err("Stack limit exceeded\n");
    if (WTERMSIG(status) == 24)
        my_putstr_err("Cputime limit exceeded\n");
    print_error_4(status);
}

void print_error_2(int status)
{
    if (WTERMSIG(status) == 7) {
        my_putstr_err("Bus error");
        if (__WCOREDUMP(status) != 0)
            my_putstr_err(" (core dumped)\n");
        else
            my_putchar('\n');
    }
    if (WTERMSIG(status) == 8) {
        my_putstr_err("Floating exception");
        if (__WCOREDUMP(status) != 0)
            my_putstr_err(" (core dumped)\n");
        else
            my_putchar('\n');
    }
    if (WTERMSIG(status) == 9)
        my_putstr_err("Killed\n");
    if (WTERMSIG(status) == 10)
        my_putstr_err("User signal 1\n");
    print_error_3(status);
}

void print_error(int status)
{
    if (WTERMSIG(status) == 1)
        my_putstr_err("Hangup\n");
    if (WTERMSIG(status) == 3)
        my_putstr_err("Quit\n");
    if (WTERMSIG(status) == 4)
        my_putstr_err("Illegal instruction\n");
    if (WTERMSIG(status) == 5)
        my_putstr_err("Trace/BPT trap\n");
    if (WTERMSIG(status) == 6) {
        my_putstr_err("Abort");
        if (__WCOREDUMP(status) != 0)
            my_putstr_err(" (core dumped)\n");
        else
            my_putchar('\n');
    }
    print_error_2(status);
}