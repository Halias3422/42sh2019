/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump_up_dowm.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 07:43:32 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 09:30:28 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		jump_up(t_pos *pos)
{
	t_pos	clone;

	clone.act_co = pos->act_co;
	clone.act_li = pos->act_li;
	clone.max_co = pos->max_co;
	clone.start_li = pos->start_li;
	clone.let_nb = pos->let_nb;
	clone.is_complete = pos->is_complete;
	clone.len_prompt = pos->len_prompt;
	while (pos->let_nb > 0)
	{
		left_arrow(pos);
		if (pos->act_co <= clone.act_co && pos->act_li < clone.act_li)
			break ;
	}
}

void		jump_down(t_pos *pos)
{
	t_pos	clone;
	int		loop;

	loop = 0;
	clone.act_co = pos->act_co;
	clone.act_li = pos->act_li;
	clone.max_co = pos->max_co;
	clone.start_li = pos->start_li;
	clone.let_nb = pos->let_nb;
	clone.is_complete = pos->is_complete;
	clone.len_prompt = pos->len_prompt;
	while (pos->ans[pos->let_nb])
	{
		if (pos->ans[pos->let_nb] == '\n')
			loop += 1 + pos->act_li - clone.act_li;
		if (loop >= 2)
			break ;
		right_arrow(pos);
		if (pos->act_co >= clone.act_co && pos->act_li > clone.act_li)
			break ;
	}
}
