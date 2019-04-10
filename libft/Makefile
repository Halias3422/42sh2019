# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/03 11:51:34 by rlegendr     #+#   ##    ##    #+#        #
#    Updated: 2019/04/10 09:41:14 by rlegendr    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME    = libft.a
PROJECT_NAME = libft
EXE = ft_libft

FLAGS   = -Wall -Werror -Wextra -g3# -fsanitize=address
CFLAGS  = $(FLAGS) -I./includes -c

C_LIBFT = libft/ft_strndup.c libft/check_num_length.c libft/ft_abs.c libft/ft_atoi.c libft/ft_atoi_base.c libft/ft_brainfuck.c libft/ft_bzero.c libft/ft_copy_part_str.c libft/ft_factorial.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isblank.c libft/ft_iscntrl.c libft/ft_isdigit.c libft/ft_isneg.c libft/ft_isprime.c libft/ft_isprint.c libft/ft_isspace.c libft/ft_itoa.c libft/ft_itoa_base.c libft/ft_itoa_base_uns.c libft/ft_lst_totaldel.c libft/ft_lstadd.c libft/ft_lstbck.c libft/ft_lstdel.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlen.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_memalloc.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memdel.c libft/ft_memmove.c libft/ft_memset.c libft/ft_power.c libft/ft_print_t_list.c libft/ft_print_tab.c libft/ft_putchar.c libft/ft_putchar_fd.c libft/ft_putendl.c libft/ft_putendl_fd.c libft/ft_putnbr.c libft/ft_putnbr_fd.c libft/ft_putstr.c libft/ft_putstr_fd.c libft/ft_range.c libft/ft_split_whitespaces.c libft/ft_sqrt.c libft/ft_strcapitalizer.c libft/ft_strcat.c libft/ft_strchr.c libft/ft_strclr.c libft/ft_strcmp.c libft/ft_strcpy.c libft/ft_strdel.c libft/ft_strdup.c libft/ft_strequ.c libft/ft_striter.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlen.c libft/ft_strmap.c libft/ft_strmapi.c libft/ft_strncat.c libft/ft_strncmp.c libft/ft_strncpy.c libft/ft_strnequ.c libft/ft_strnew.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strrev.c libft/ft_strsplit.c libft/ft_strstr.c libft/ft_strsub.c libft/ft_strtrim.c libft/ft_swap_let_string.c libft/ft_tabdel.c libft/ft_tolower.c libft/ft_toupper.c libft/get_next_line.c libft/ft_free_void.c libft/ft_strjoinf.c libft/ft_strnjoinnf.c
C_PRINTF = ft_printf/add_conversion.c ft_printf/add_flag2.c ft_printf/add_flags.c ft_printf/bonus_conversion_type_1.c ft_printf/bonus_conversion_type_2.c ft_printf/bonus_conversion_type_3.c ft_printf/conversion_type.c ft_printf/conversion_type2.c ft_printf/determ_data.c ft_printf/ft_printf.c ft_printf/handle_flags_order.c ft_printf/handle_float.c ft_printf/handle_prec_and_width.c ft_printf/others.c ft_printf/others2.c ft_printf/print_colors.c ft_printf/print_printf.c

HEADERS = ./includes/libft.h \
		  ./includes/ft_printf.h

O_LIBFT  = $(C_LIBFT:.c=.o)
O_PRINTF = $(C_PRINTF:.c=.o)
DIR_O    = objects
MAIN = main/main_printf.c
CC = @gcc

all: $(NAME)

$(NAME): $(O_LIBFT) $(O_PRINTF) $(HEADERS)
	@ar rcs $(NAME) $(O_LIBFT) $(O_PRINTF)
	@ranlib $(NAME)
	@echo "\033[1;36m$(PROJECT_NAME)		\033[1;32m[✓]\033[0;37m"

(DIR_O)/%.o: %.c
	$(CC) $(CFLAGS) $<

exe : $(NAME)
	@gcc -o $(EXE) -I./includes $(MAIN) $(NAME)

clean:
	@rm -rf $(O_LIBFT) $(O_PRINTF)
	@rm -rf ./includes/*.gch
	@rm -rf $(EXE).dSYM
	@rm -f .DS_Store
	@echo "\033[1;33mclean 	\033[1;36m$(PROJECT_NAME)	\033[1;32m[✓]\033[0;37m"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(EXE)
	@rm -rf a.out
	@echo "\033[1;33mfclean 	\033[1;36m$(PROJECT_NAME)	\033[1;32m[✓]\033[0;37m"

re: fclean all

.PHONY: clean fclean all re 
