##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

.RECIPEPREFIX +=

CC      =       gcc

SRC     =   minishell_main.c \
            minishell_useful.c \
            minishell_get_info.c \
            minishell_command.c \
            minishell_env.c \
            minishell_get_put.c \
            minishell_errors.c \
            minishell_options.c \
            minishell_cd.c \
            src/my_strcpy.c \
            src/my_putchar.c \
            src/my_putstr.c \
            src/my_put_nbr.c \
            src/get_next_line.c \
            src/my_strcmp.c \
            src/my_strncmp.c \
            src/my_strcat.c \
            src/my_putstr_err.c \
            src/my_putchar_err.c \
            src/my_str_isalpha.c

OBJ     =       $(SRC:.c=.o)

NAME    =       mysh

CFLAGS  =       -W -Wextra -Wall -ansi -pedantic -g -std=c99 -I ./include

all:    $(NAME)

$(NAME):	$(OBJ)
    $(CC) $(OBJ) -o $(NAME) $(CFLAGS)
    rm -f $(OBJ)

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re:		fclean all
