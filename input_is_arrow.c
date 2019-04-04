/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_arrow.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 15:11:48 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 16:12:21 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		right_arrow(char *buf, t_pos *pos)
{
	if (pos->act_co == pos->max_co)
	{
		pos->act_co = 0;
		pos->act_li += 1;
	}
	else
		pos->act_co++;
	pos->let_nb++;
	if (pos->let_nb % pos->max_co == 0)
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co - 1, pos->act_li),
				1, ft_putchar);
	tputs(buf, 1, ft_putchar);
}

void		left_arrow(char *buf, t_pos *pos)
{
	//	if (pos->let_nb % pos->max_co == 0 && pos->act_li > pos->start_li)
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_li--;
		pos->act_co = pos->max_co;
	}
	else
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	pos->let_nb--;
	tputs(buf, 1, ft_putchar);
}

t_hist		*find_arrow(char *buf, t_pos *pos, t_hist *hist)
{
	/*	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		hist = move_through_history(hist, pos, "up");
		else if (ft_strncmp(buf + 1, "[B", 2) == 0)
		hist = move_through_history(hist, pos, "down");
		else*/ if (pos->let_nb < (int)ft_strlen(pos->ans) &&
				ft_strncmp(buf + 1, "[C", 2) == 0)
			right_arrow(buf, pos);
		else if (pos->let_nb > 0 && pos->act_co >= 0 &&
				ft_strncmp(buf + 1, "[D", 2) == 0)
			left_arrow(buf, pos);
		return (hist);
}
