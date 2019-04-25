# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/04/24 18:02:46 by mjalenqu     #+#   ##    ##    #+#        #
#    Updated: 2019/04/24 11:23:58 by mjalenqu    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = 21sh

LIB_PATH = libft/libft.a
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
SRC_NAME =	calcul_line.c check_input.c escape_code.c history.c init_termcaps.c\
			input_is_entry.c input_is_printable_char.c main_termcaps.c move_through_history.c\
			termcaps_tools.c
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = termcaps.h

INC = $(addprefix $(INC_PATH),$(INC_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
FLAG += -Wall -Werror -Wextra -g3 -fsanitize=address
FLAG_END = -lcurses
NORME = norminette

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
	@echo "\n\n$(ORANGE)Compilation de la libft : "
	@make -C libft
	@gcc $(FLAG) -o $@ $(OBJ) $(FLAG_END) $(LIB_PATH) -Iinclude
	@echo "$(LIGHT_YELLOW)$(NAME) compilé et prêt à l'usage !\033[0m\n"

$(OBJ_PATH):
	@echo "$(SRC_PATH)"
	@echo "$(OBJ_PATH)"
	@echo "$(INC)"
	@mkdir -p obj 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@gcc $(FLAG) -g -I $(INC_PATH) -o $@ -c $<
	@echo "$(LIGHT_RED).\c"

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo "$(LIGHT_PINK)Suppression des .o de "$(NAME)"\n"

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "$(PINK)Suppression de" $(NAME)"\n"

re : fclean all