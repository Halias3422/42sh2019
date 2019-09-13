# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/04 18:02:46 by mjalenqu     #+#   ##    ##    #+#        #
#    Updated: 2019/09/13 09:21:11 by vde-sain    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = 21sh

LIB_PATH = libft/libft.a
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

SRC_LINE = $(addprefix line_edit/, \
				calcul_line.c check_error.c check_input.c control_search_history_calcul_pos.c\
				control_search_history.c control_search_history_calcul_lines.c \
				copy_tools.c copy.c cut.c env.c escape_code.c ft_errno.c\
				history_expansion.c history_expansion_types.c\
				history_expansion_calculate.c\
				history.c initialisation_stock.c input_is_entry.c tools.c\
				input_is_printable_char.c input_is_remove_char.c jump_up_down.c jump.c\
				move_through_history.c print_ans.c search_in_history.c signal.c tab_key_var.c\
				start_termcaps.c tab_key.c tab_key_all_path.c tab_key_auto_complete.c tab_key_current_dir.c\
				tab_key_sort.c tab_key_struct.c tab_key_tools_calcul_print.c tab_key_tools_manip.c\
				token.c token_check_close.c token_check_open.c token_free.c token_heredoc_close.c\
				token_heredoc_open.c token_init.c init_alias.c debug.c)

SRC_LEX = $(addprefix lexeur/, \
				back_slash.c back_slash_end.c back_slash_tools.c error.c fill_lexeur.c lexeur.c redirection.c redirection_tools.c \
				error_lex.c)

SRC_EXEC = $(addprefix exec/, \
				alias.c builtins.c launch_process.c launch_job.c exec.c process.c tools.c \
				job_controll.c job_function.c job_notification.c)

SRC_REP = $(addprefix replace/, \
				alias.c var_replace.c var_tool.c tool_cnt.c tool_list.c replace.c tool.c quote.c alias_tools.c free_file.c alias_change_type.c alias_cnt.c)

SRC_BUILTIN = $(addprefix builtin/, \
				ft_test.c ft_test_int.c ft_echo.c ft_cd.c ft_set.c ft_type.c ft_export.c \
				ft_unset.c ft_fc.c tool.c ft_fg.c ft_bg.c ft_jobs.c ft_exit.c fc_get_args.c \
				fc_get_flags.c fc_execute_l_flag.c fc_execute_s_flag.c fc_execute_e_flag.c \
				fc_tools.c fc_prepare_e_flag.c fc_s_replace_pattern.c ft_hash.c \
				hash_d_flag.c)

SRC_MAIN = $(addprefix main/, main.c)

SRC_HASH = $(addprefix hash/, hash.c hash_tools.c)

SRC_NAME = $(SRC_EXEC) $(SRC_LEX) $(SRC_LINE) $(SRC_MAIN) $(SRC_REP) $(SRC_BUILTIN) $(SRC_HASH)

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = termcaps.h

INC = $(addprefix $(INC_PATH), $(INC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAG += -Wall -Werror -Wextra -O3 -g3 -fsanitize=address
FLAG_END = -lcurses
NORME = norminette

BLUE=\033[0;38;5;123m
DARK_BLUE = \033[0;38;5;110m
GREEN = \033[0;32m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_YELLOW = \033[1;33;5;121m
LIGHT_RED = \033[1;31;5;121m
FLASH_GREEN = \033[33;32m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(NAME) : $(OBJ_PATH) $(OBJ) Makefile
	@echo  "\n42sh loaded"
	@make -C libft
	@echo "$(YELLOW)Libft$(RESET):\t...$(GREEN)\t[OK]"
	@gcc $(FLAG) -o $@ $(OBJ) $(FLAG_END) $(LIB_PATH) -I include
	@echo "$(YELLOW)$(NAME)$(RESET):\t...$(GREEN)\t[OK]"
#	@./21sh

$(OBJ_PATH):
	@mkdir -p obj 2> /dev/null
	@mkdir -p obj/line_edit 2> /dev/null
	@mkdir -p obj/lexeur 2> /dev/null
	@mkdir -p obj/replace 2> /dev/null
	@mkdir -p obj/exec 2> /dev/null
	@mkdir -p obj/builtin 2> /dev/null
	@mkdir -p obj/main 2> /dev/null
	@mkdir -p obj/ft_printf 2> /dev/null
	@mkdir -p obj/hash 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@gcc $(FLAG) -g -I $(INC_PATH) -o $@ -c $<
	@echo "$(LIGHT_GREEN).\c"

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo ".o\tof\t$(YELLOW)$(NAME)$(RESET):\t$(RED)[-]$(RESET)"

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "./$(NAME)\tof\t$(YELLOW)$(NAME)$(RESET):\t$(RED)[-]\n"

re : fclean all
