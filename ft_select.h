/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 11:17:23 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <curses.h>

typedef struct		s_pos
{
	int				act_co;
	int				act_li;
	int				tot_co;
	int				tot_li;
	char			*ans;
	int				history;
}					t_pos;

typedef struct		s_hist
{
	struct s_hist	*next;
	struct s_hist	*prev;
	char			*cmd;
}					t_hist;

t_hist				*create_history(t_pos *pos, t_hist *hist);
t_hist				*move_through_history(t_hist *hist, t_pos *pos, char *usage);

#endif
