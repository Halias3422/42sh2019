/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_arrow.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 15:11:48 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 11:00:10 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		right_arrow(char *buf, t_pos *pos)
{
	if (pos->act_co == pos->max_co - 1 || pos->ans[pos->let_nb] == '\n')
	{
		pos->act_co = 0;
		pos->act_li += 1;
	}
	else
	{
		pos->act_co++;
		tputs(buf, 1, ft_putchar);
	}
	pos->let_nb++;
	if (pos->act_co % pos->max_co == 0)
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co - 1 -
			pos->len_prompt, pos->act_li), 1, ft_putchar);
}

int			len_of_previous_line(t_pos *pos)
{
	int		len;
	int		i;

	i = pos->let_nb - 2;
	len = 0;
	while (pos->ans[i] > 0 && pos->ans[i] != '\n')
	{
		i--;
		len++;
	}
	if (pos->act_li == pos->start_li)
		len += pos->len_prompt;
	pos->debug4 = len;
	return (len);
}

void		left_arrow(char *buf, t_pos *pos)
{
	pos->debug2 = pos->act_co;
	pos->debug3 = pos->act_li;
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->debug = 5;
		pos->act_li--;
		if (pos->ans[pos->let_nb - 1] == '\n')
		{
			pos->debug = 1;
			pos->act_co = len_of_previous_line(pos);
		}
		else
		{
			pos->debug = 2;
			pos->act_co = pos->max_co - 1;
		}
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co,
			pos->act_li), 1, ft_putchar);
	}
	else if (pos->is_complete == 0 && pos->let_nb > 0 && pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == 2)
	{
		pos->debug = 3;
		return ;
	}
	else
	{
		pos->debug = 4;
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
		tputs(buf, 1, ft_putchar);
		//tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	}
	pos->let_nb--;
}

t_hist		*find_arrow(char *buf, t_pos *pos, t_hist *hist)
{
	if (ft_strncmp(buf + 1, "[A", 2) == 0 && pos->is_complete == 1)
		hist = move_through_history(hist, pos, "up");
	else if (ft_strncmp(buf + 1, "[B", 2) == 0 && pos->is_complete == 1)
		hist = move_through_history(hist, pos, "down");
	else if (pos->let_nb < (int)ft_strlen(pos->ans) &&
			ft_strncmp(buf + 1, "[C", 2) == 0)
		right_arrow(buf, pos);
	else if (pos->let_nb > 0 && pos->act_co >= 0 &&
			ft_strncmp(buf + 1, "[D", 2) == 0)
		left_arrow(buf, pos);
	return (hist);
}
