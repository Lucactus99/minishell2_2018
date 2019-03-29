##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

.RECIPEPREFIX +=

CC		:= gcc -g

NAME		:= mysh
FILES		:= cd command env errors_2 errors get_info get_put main options useful arguments binary command_double_pipes command_simple_pipe find_command get_commands manage redirections redirections_errors
LIB_FILES       := get_next_line my_put_nbr my_putchar_err my_putchar my_putstr_err my_putstr my_str_isalpha my_strcat my_strcmp my_strcpy my_strncmp transform_2d

SRC_NAMES 	:= $(addsuffix .c, $(FILES))
LIB_NAMES       := $(addsuffix .c, $(LIB_FILES))
SRC		:= $(addprefix src/, $(SRC_NAMES))
LIB             := $(addprefix src/lib/, $(LIB_NAMES))

CINC		:= -I include/
CFLAGS		:= -W -Wall -Wextra

OBJ             := $(SRC:src/%.c=%.o) \
                   $(LIB:src/lib/%.c=%.o)

RED             := \033[0;31m
CYAN            := \033[0;36m
GOLD            := \033[0;33m
GREEN           := \033[0;32m
WHITE           := \033[0;0m

PREFIX		:= $(CYAN) "[$(NAME)]"

all:        $(NAME)

%.o: src/%.c
        @$(CC) -c $(CFLAGS) $(CINC) $^ -o $@
        @echo "$(PREFIX) $(GREEN)$^ $(GOLD)=> $(GREEN)$@"
%.o: src/lib/%.c
        @$(CC) -c $(CFLAGS) $(CINC) $^ -o $@
        @echo "$(PREFIX) $(GREEN)$^ $(GOLD)=> $(GREEN)$@"

$(NAME):        $(OBJ)
        @echo "$(GOLD)Compiling...$(WHITE)\r"
        @$(CC) $(OBJ) -o $(NAME) $(CINC) $(CFLAGS)
        @echo "$(GOLD)Compiled !$(WHITE)"
        @echo "$(RED)Delete $(GOLD)$(PWD)/*.o$(WHITE)"
        @rm -rf $(OBJ)

clean:
        @echo "$(RED)Delete $(GOLD)$(PWD_PATH)/*.o$(WHITE)"
        @rm -rf $(OBJ)

fclean:         clean
        @echo "$(RED)Delete $(GOLD)$(PWD)/$(NAME)$(WHITE)"
        @rm -rf $(NAME)

re:             fclean all
