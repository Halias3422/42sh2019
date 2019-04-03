# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/11 11:27:41 by rlegendr     #+#   ##    ##    #+#        #
#    Updated: 2019/04/03 10:48:16 by vde-sain    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = ft_select

SRC = history.c \
	  init_ft_select.c \
	  check_input.c \
	  input_is_arrow.c \
	  handle_ans.c \
	  util_tools.c

#srcs_ls/ft_ls.c \
#	  srcs_ls/sort_list_ls.c

OBJ = $(SRC:.c=.o)

OBJ_DIR = srcs_ls/

CC = gcc

FLAGS = -Wall -Werror -Wextra -g3# -fsanitize=address

LIBFT = ./libft/

HEADER = ft_select.h

LIBFT.A = ./libft/libft.a

all: libs $(NAME)

$(NAME): $(SRC) $(HEADER) $(LIBFT.A)
	@$(CC) -o $(NAME) $(FLAGS) $(SRC) -I./includes $(LIBFT.A) -ltermcap
	@rm -rf $(NAME).dSYM
	@ echo "\033[1;36m$(NAME)		\033[1;32m[✓]\033[0m"

libs:
	@ make -C libft/

#$(OBJ_DIR)%.o: %.c
#		@$(CC) $(FLAGS) $(SRC) -I./includes

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
