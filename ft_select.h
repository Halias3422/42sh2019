/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 01:36:45 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>

typedef struct		s_pos
{
	int				act_co;
	int				act_li;
	int				start_li;
	int				start_co;
	int				max_co;
	int				max_li;
	char			*ans;
	int				len_ans;
	int				history;
	int				let_nb;
	int				debug;
	char			*prompt;
	int				len_prompt;
}					t_pos;

typedef struct		s_hist
{
	struct s_hist	*next;
	struct s_hist	*prev;
	char			*cmd;
}					t_hist;

/*
**INIT_FT_SELECT.C
*/

int					main(void);
void				init_terminfo(void);
int					init_pos(t_pos *pos, char *buf);
void				get_start_info(char *buf, t_pos *pos);
int					check_term(void);

/*
**CHECK_INPUT.C
*/

t_hist				*check_input(char *buf, t_pos *pos, t_hist *hist);
void				input_is_backspace(t_pos *pos);
void				input_is_entry(t_pos *pos, t_hist *hist);
void				input_is_printable_char(t_pos *pos, char *buf);

/*
**INPUT_IS_ARROW.C
*/

t_hist				*find_arrow(char *buf, t_pos *pos, t_hist *hist);
void				left_arrow(char *buf, t_pos *pos);
void				right_arrow(char *buf, t_pos *pos);

/*
**HANDLE_ANS.C
*/

void				print_ans(t_pos *pos);
void				fill_char_ans(char *buf, t_pos *pos);
void				remove_char_ans(t_pos *pos);

/*
**HISTORY.C
*/

void				init_t_hist(t_hist *hist);
t_hist				*create_history(t_pos *pos, t_hist *hist);
t_hist				*ft_list_back(t_hist *head, t_hist *hist);
t_hist				*move_through_history(t_hist *hist, t_pos *pos,
					char *usage);

/*
**TERMCAPS_TOOLS.C
*/

void				clean_screen(t_pos *pos);
void				check_poussin(char c);
void				print_info(t_pos *pos);
void				print_hist(t_pos *pos, t_hist *hist);

#endif
