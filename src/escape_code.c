/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   escape_code.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:05:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 08:09:45 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void            right_arrow(char *buf, t_pos *pos)
{
	if (pos->act_co == pos->max_co - 1 || pos->ans[pos->let_nb] == '\n')
	{
		pos->act_co = 0;
		pos->act_li += 1;
	}
	else
		pos->act_co++;
	tputs(buf, 1, ft_putchar);
	pos->let_nb++;
}

void            left_arrow(char *buf, t_pos *pos)
{
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_li--;
		if (pos->ans[pos->let_nb - 1] == '\n')
			pos->act_co = len_of_previous_line(pos);
		else
			pos->act_co = pos->max_co - 1;
	}
	else if (pos->is_complete == 0 && pos->let_nb > 0 && pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == 2)
		return ;
	else
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	tputs(buf, 1, ft_putchar);
	pos->let_nb -= 1;
}

void		jump_right(t_pos *pos)
{
	if (pos->let_nb >= pos->len_ans)
		return ;
	if (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
	{
		while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
		{
			pos->let_nb++;
			if (pos->act_co == pos->max_co && pos->ans[pos->let_nb])
			{
				pos->act_co = 0;
				pos->act_li++;
			}
			else
				pos->act_co++;
		}
	}
	while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 1)
	{
		pos->let_nb++;
		if (pos->act_co == pos->max_co && pos->ans[pos->let_nb])
		{
			pos->act_co = 0;
			pos->act_li++;
		}
		else
			pos->act_co++;
	}
}

void		jump_left(char *buf, t_pos *pos)
{
	(void)buf;
	if (pos->let_nb == 0)
		return ;
	if (ft_isspace(pos->ans[pos->let_nb]) == 0 && ft_isspace(pos->ans[pos->let_nb - 1]) == 1)
	{
		pos->let_nb--;
		pos->act_co--;
	}
	if (ft_isspace(pos->ans[pos->let_nb]) == 1)
	{
		while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb]) == 1)
		{
			pos->debug2 = pos->ans[pos->let_nb];
			pos->let_nb--;
			if (pos->act_co > 0)
				pos->act_co--;
			else if (pos->act_co == 0 && pos->act_li > pos->start_li)
			{
				pos->act_co = pos->max_co;
				pos->act_li--;
			}
		}
	}
	while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb]) == 0)
	{
		if (ft_isspace(pos->ans[pos->let_nb - 1]) == 1)
			break ;
		pos->let_nb--;
		if (pos->act_co > 0)
			pos->act_co--;
		else if (pos->act_co == 0 && pos->act_li > pos->start_li)
		{
			pos->act_co = pos->max_co;
			pos->act_li--;
		}
	}
//	pos->let_nb++;
//	pos->act_co++;
	pos->debug = pos->act_co;
	pos->debug3 = pos->let_nb;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		find_jump(char *buf, t_pos *pos)
{
	if (ft_strcmp(buf + 2, "[D") == 0)
		jump_left(buf, pos);
	else if (ft_strcmp(buf + 2, "[C") == 0)
		jump_right(pos);
}

t_hist		*escape_code(char *buf, t_pos *pos, t_hist *hist)
{
	if (buf && buf[1] == 27)
		find_jump(buf, pos);
	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		hist = move_through_history(hist, pos, "up");
	else if (ft_strncmp(buf + 1, "[B", 2) == 0)
		hist = move_through_history(hist, pos, "down");
	if (pos->let_nb < (int)ft_strlen(pos->ans) &&
			ft_strncmp(buf + 1, "[C", 2) == 0)
		right_arrow(buf, pos);
	else if (pos->let_nb > 0 && ft_strncmp(buf + 1, "[D", 2) == 0)
		left_arrow(buf, pos);
	return (hist);
}
