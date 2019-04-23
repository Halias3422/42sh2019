# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/11 11:27:41 by rlegendr     #+#   ##    ##    #+#        #
#    Updated: 2019/04/23 17:26:08 by mjalenqu    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = 21sh

LIB_PATH = libft/libft.a
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

SRC_NAME = 	1_init_termcaps.c 1_history.c 1_move_through_history.c \
		1_termcaps_tools.c 1_check_input.c 1_input_is_printable_char.c \
		1_handle_ans.c 1_input_is_arrow.c main_termcaps.c
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = ft_select.h

INC = $(addprefix $(INC_PATH),$(INC_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
FLAG += -Wall -Werror -Wextra -g3 #-fsanitize=address
FLAG_END = -lcurses
NORME = norminette

CC = gcc

LIBFT = ./libft/

LIBFT.A = ./libft/libft.a

BLUE=\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[0;38;5;110m
GREEN = \033[0;38;5;111m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_YELLOW = \033[1;33;5;121m
LIGHT_RED = \033[1;31;5;121m
FLASH_GREEN = \033[33;32m
ORANGE = \033[1;38;2;255;100;0m

all: $(NAME)

$(NAME) : $(OBJ_PATH) $(OBJ) Makefile
	@make -C libft
	@gcc $(FLAG) -o $@ $(OBJ) $(FLAG_END) $(LIB_PATH) -Iincludes
	@rm -rf $(NAME).dSYM
	@ echo "\033[1;36m$(NAME)		\033[1;32m[✓]\033[0m"

$(OBJ_PATH):
	@mkdir -p obj 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@gcc $(FLAG) -g -I $(INC_PATH) -o $@ -c $<
	
clean:
	@rm -rf $(OBJ_PATH)
	@rm -rf includes/*.gch
	@rm -rf $(NAME).dSYM
	@make -C libft/ clean
	@echo "\033[1;33mclean 	\033[1;36m$(NAME)	\033[1;32m[✓]\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[1;33mfclean 	\033[1;36m$(NAME)	\033[1;32m[✓]\033[0m"

re: fclean all

.PHONY : all clean fclean re
