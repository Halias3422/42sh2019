/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 16:20:38 by rlegendr    ###    #+. /#+    ###.fr     */
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
	int				total;
	int				actual;
	char			*ans;
}					t_pos;

#endif
