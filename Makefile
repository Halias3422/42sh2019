# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/11 11:27:41 by rlegendr     #+#   ##    ##    #+#        #
#    Updated: 2019/04/24 09:53:41 by vde-sain    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = ft_select

SRC = init_termcaps.c \
	  termcaps_tools.c \
	  history.c \
	  check_input.c \
	  input_is_printable_char.c \
	  escape_code.c \
	  calcul_line.c \
	  input_is_entry.c \
	  move_through_history.c \
	  main_termcaps.c 
# 	init_termcaps.c \
		history.c \
		move_through_history.c \
		termcaps_tools.c \
		check_input.c \
		input_is_printable_char.c \
		handle_ans.c \
		input_is_arrow.c \
		input_is_entry.c \
		main_termcaps.c


OBJ = $(SRC:.c=.o)

OBJ_DIR = srcs_ls/

CC = gcc

FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

LIBFT = ./libft/

HEADER = termcaps.h

LIBFT.A = ./libft/libft.a

all: libs $(NAME)

$(NAME): $(SRC) $(HEADER) $(LIBFT.A)
	@$(CC) -o $(NAME) $(FLAGS) $(SRC) -I./includes $(LIBFT.A) -ltermcap
	@rm -rf $(NAME).dSYM
	@ echo "\033[1;36m$(NAME)		\033[1;32m[✓]\033[0m"

libs:
	@ make -C libft/

%.o: %.c
	@$(CC) $(FLAGS) $(SRC) -I./includes $(LIBFT.A) -ltermcap

clean:
	@rm -f $(OBJ)
	@rm -f includes/*.gch
	@rm -rf $(NAME).dSYM
	@(cd $(LIBFT) && $(MAKE) $@)
	@echo "\033[1;33mclean 	\033[1;36m$(NAME)	\033[1;32m[✓]\033[0m"

fclean: clean
	@rm -f $(NAME)
	@(cd $(LIBFT) && $(MAKE) $@)
	@echo "\033[1;33mfclean 	\033[1;36m$(NAME)	\033[1;32m[✓]\033[0m"

re: fclean all

.PHONY : all clean fclean re
