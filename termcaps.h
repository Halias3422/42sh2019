/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   termcaps.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 09:58:38 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>

/*
** Signal define
*/

# define RESIZING 28

typedef struct		s_pos
{
	int				act_co;
	int				act_li;
	int				start_li;
	int				start_co;
	int				max_co;
	int				max_li;
	int				ans_printed;
	char			*ans;
	char			*saved_ans;
	int				is_complete;
	int				was_incomplete;
	int				len_ans;
	int				let_nb;
	int				let_nb_saved;
	int				history;
	int				history_mode;
	int				history_loop;
	char			*prompt;
	int				len_prompt;
	int				debug;
	int				debug2;
	int				debug3;
	int				debug4;
	int				debug5;
	struct termios	old_term;
	struct termios	my_term;
}					t_pos;

typedef struct		s_inter
{
	int				sg_quote;
	int				db_quote;
	int				bracket;
	int				parenthesis;
	int				a_quote;
	int				db_and;
	int				pipe;
	int				db_pipe;
}					t_inter;

typedef struct		s_hist
{
	struct s_hist	*next;
	struct s_hist	*prev;
	char			*cmd;
	int				cmd_no;
}					t_hist;

/*
** CALCUL_LINE
*/

int					get_len_with_lines(t_pos *pos);
int					go_to_let_nb_saved(t_pos *pos);
int					len_of_previous_line(t_pos *pos);
int					count_nb_line(t_pos *pos, int *j);

/*
** CHECK_ERROR
*/

int					check_term(void);

/*
** CHECK_INPUT.C
*/

t_hist				*check_input(char *buf, t_pos *pos, t_hist *hist);

/*
** ESCAPE_CODE
*/

t_hist				*escape_code(char *buf, t_pos *pos, t_hist *hist);
void				right_arrow(t_pos *pos);
void				left_arrow(t_pos *pos);

/*
** HISTORY.C
*/

void				free_t_hist(t_hist *hist);
void				init_t_hist(t_hist *hist);
t_hist				*add_list_back_hist(t_hist *hist);
t_hist				*create_history(t_pos *pos, t_hist *hist);

/*
** INITIALISATION_STOCK
*/

void				init_terminfo(t_pos *pos);
void				init_pos(t_pos *pos, char *buf);
void			*stock(t_pos *pos, int usage);

/*
** INPUT_IS_ENTRY
*/

int					find_missing_quote(char *str);
t_hist				*input_is_entry(t_pos *pos, t_hist *hist, char *buf);

/*
** INPUT_IS_PRINTABLE_CHAR
*/
void				prompt_is_on_last_char(t_pos *pos);
void				input_is_printable_char(t_pos *pos, char *buf);

/*
** INPUT_IS_REMOVE_CHAR
*/

void				input_is_delete(t_pos *pos);
int					input_is_backspace(t_pos *pos);

/*
** MOVE_THROUGHT_HISTORY
*/

t_hist				*move_through_history(t_hist *hist,
						t_pos *pos, char *usage);

/*
** PRINT_ANS
*/

void				prepare_to_print(t_pos *pos, char *buf);
void				print_ans(t_pos *pos, int i, int act_coi);

/*
** SEARCH_IN_HISTORY
*/

t_hist				*search_up_complete_in_history(t_hist *hist, t_pos *pos);
t_hist				*search_down_complete_in_history(t_hist *hist, t_pos *pos);

/*
** SIGNAL
*/

void				signal_list(void);

/*
** TOOLS
*/

void				clean_at_start(t_pos *pos);
void				short_update(t_pos *pos, int len);
void				update_position(t_pos *pos);

/*
** START_TERMCAPS
*/

char				*termcaps42sh(char *prompt, t_pos *pos, t_hist *hist);
void				print_prompt(t_pos *pos);

#endif
