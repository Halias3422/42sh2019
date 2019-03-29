/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 11:16:11 by rlegendr    ###    #+. /#+    ###.fr     */
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
}					t_pos;

#endif
