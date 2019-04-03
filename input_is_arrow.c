/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_arrow.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 10:13:47 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 11:11:01 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		right_arrow(char *buf, t_pos *pos)
{
	if (pos->let_nb == pos->max_co)
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->act_li + 1),
				1, ft_putchar);
	tputs(buf, 1, ft_putchar);
	if (pos->act_co == pos->max_co)
	{
		pos->act_co = 0;
		pos->act_li += 1;
	}
	else
		pos->act_co++;
	pos->let_nb++;
	if (pos->act_co == 0 && pos->let_nb > 0)
		pos->act_li++;
}

void		left_arrow(char *buf, t_pos *pos)
{
	pos->let_nb--;
	if (pos->let_nb % pos->max_co == 0)
		pos->act_li--;
	tputs(buf, 1, ft_putchar);
	pos->act_co -= pos->act_co == 0 ? 0 : 1;
}

t_hist		*find_arrow(char *buf, t_pos *pos, t_hist *hist)
{
	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		hist = move_through_history(hist, pos, "up");
	else if (ft_strncmp(buf + 1, "[B", 2) == 0)
		hist = move_through_history(hist, pos, "down");
	else if (pos->let_nb < (int)ft_strlen(pos->ans) &&
			ft_strncmp(buf + 1, "[C", 2) == 0)
		right_arrow(buf, pos);
	else if (pos->let_nb > 0 && pos->act_co >= 0 &&
			ft_strncmp(buf + 1, "[D", 2) == 0)
		left_arrow(buf, pos);
	return (hist);
}
