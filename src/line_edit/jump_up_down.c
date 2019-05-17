/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump_up_dowm.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 07:43:32 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 13:51:17 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int			check_if_backslash_n(t_pos *pos, int i, int usage)
{
	if (usage == 0)
	{
		while (pos->ans[i] && i <= pos->let_nb)
		{
			if (pos->ans[i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
	while (pos->ans[i])
	{
		if (pos->ans[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void		jump_up_with_backslash_n(t_pos *pos)
{
	int		prev_act_co;

	prev_act_co = pos->act_co;
	while (prev_act_co-- > 0)
		pos->let_nb--;
	prev_act_co = len_of_previous_line(pos);
	if (prev_act_co < pos->act_co)
	{
		pos->act_co = prev_act_co;
		pos->let_nb--;
	}
	else if (prev_act_co == pos->max_co)
	{
		pos->act_co = 0;
		pos->let_nb--;
	}
	else
		pos->let_nb -= prev_act_co - pos->act_co + 1;
	pos->act_li--;
	if (pos->let_nb < 0)
	{
		pos->let_nb = 0;
		pos->act_co = 2;
	}
}

void		jump_up(t_pos *pos)
{
	if (check_if_backslash_n(pos, 0, 0) == 0 || (pos->is_complete == 0
			&& pos->let_nb - pos->max_co >= pos->let_nb_saved - 2))
	{
		pos->let_nb -= pos->max_co;
		if (pos->is_complete == 1)
			short_update(pos, go_to_let_nb(pos));
		else
			pos->act_li--;
		if (pos->let_nb < 0)
			pos->let_nb = 0;
		if ((pos->is_complete == 0 && pos->let_nb <= pos->let_nb_saved))
		{
			pos->act_co = 2;
			pos->let_nb = pos->let_nb_saved;
		}
	}
	else if (pos->is_complete == 1)
		jump_up_with_backslash_n(pos);
}

void		jump_down_with_backslash_n(t_pos *pos, int tmp_let_nb,
			int tmp_act_co, int first_act_co)
{
	while (first_act_co > 0 && tmp_let_nb > 0)
	{
		first_act_co--;
		tmp_let_nb--;
	}
	while (pos->ans[tmp_let_nb] != '\n' && first_act_co < pos->max_co)
	{
		first_act_co++;
		tmp_let_nb++;
	}
	pos->debug = first_act_co;
	if (first_act_co < pos->max_co)
		tmp_let_nb++;
	while (pos->ans[tmp_let_nb] != '\n')
	{
		if (tmp_act_co == pos->act_co)
			break ;
		tmp_act_co++;
		tmp_let_nb++;
	}
	if (first_act_co == pos->max_co)
		tmp_let_nb -= 1;
	if (tmp_act_co < pos->act_co)
		pos->act_co = tmp_act_co;
	pos->let_nb = tmp_let_nb;
	pos->act_li++;
}

void		jump_down(t_pos *pos, int i)
{
	if (check_if_backslash_n(pos, pos->let_nb, 1) == 0 &&
		pos->act_co + ft_strlen(pos->ans) - pos->let_nb > pos->max_co)
	{
		if (pos->let_nb + pos->max_co > ft_strlen(pos->ans))
		{
			while (i > 0 && pos->ans[i] != '\n')
				i--;
			pos->act_co = ((ft_strlen(pos->ans) - i) % pos->max_co) - 1;
			if (i == 0)
				pos->act_co = (ft_strlen(pos->ans) % pos->max_co) + 2;
			if (pos->is_complete == 0)
				pos->act_co = ((ft_strlen(pos->ans) - pos->let_nb_saved)
						% pos->max_co) + 2;
			pos->let_nb = ft_strlen(pos->ans);
		}
		else
			pos->let_nb += pos->max_co;
		pos->act_li++;
	}
	else if (check_if_backslash_n(pos, pos->let_nb, 1) == 1)
		jump_down_with_backslash_n(pos, pos->let_nb, 0, pos->act_co);
//	if (pos->let_nb > ft_strlen(pos->ans))
//	{
//			pos->act_co -= pos->let_nb - ft_strlen(pos->ans);
//			pos->let_nb = ft_strlen(pos->ans);
//	}
}
