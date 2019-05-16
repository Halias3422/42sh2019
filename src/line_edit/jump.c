/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 14:23:16 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 15:44:25 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	jump_left(t_pos *pos)
{
	if (pos->is_complete == 0 && pos->act_co == 2)
		return ;
	if (pos->let_nb == 0)
		return ;
	if (ft_isspace(pos->ans[pos->let_nb]) == 0 && ft_isspace(pos->ans[pos->let_nb - 1]) == 1)
	{
		pos->let_nb--;
		pos->act_co--;
	}
	if (ft_isspace(pos->ans[pos->let_nb]) == 1)
		while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb]) == 1)
			left_arrow(pos);
	while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb - 1]) == 0)
		pos->let_nb -= 1;
//	int len = go_to_let_nb(pos);
	short_update(pos, go_to_let_nb(pos));
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void	jump_right(t_pos *pos)
{
	if (pos->let_nb >= pos->len_ans)
		return ;
	if (pos->is_complete == 0 && pos->ans && pos->let_nb > 0 && pos->ans[pos->let_nb] == '\n')
		return ;
	if (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
	{
		while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
			right_arrow(pos);
	}
	while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 1)
		right_arrow(pos);
}

void	go_hard(t_pos *pos)
{
/*	if (pos->is_complete == 0)
	{*/
		while (pos->ans[pos->let_nb])
		{
			if (pos->act_co == pos->max_co - 1 || pos->ans[pos->let_nb] == '\n')
			{
				pos->act_co = 0;
				pos->act_li++;
			}
			else
				pos->act_co++;
			pos->let_nb++;
		}
/*	}
	else
	{
		while (pos->ans[pos->let_nb] != '\0')
		{
			if (pos->ans[pos->let_nb + 1] == '\n')
			{
				pos->act_co = 0;
				pos->act_li++;
			}
			else
				pos->act_co++;
			pos->let_nb++;
		}
	}
*/	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void	or_go_home(t_pos *pos)
{
	if (pos->is_complete == 0)
	{
		while (pos->let_nb > 0 && (pos->ans[pos->let_nb - 1] != '\n'))
		{
			pos->let_nb--;
			if (pos->act_co == 0)
			{
				pos->act_co = pos->max_co - 1;
				pos->act_li--;
			}
			else
				pos->act_co--;
		}
	}
	else
	{
		pos->act_co = pos->start_co;
		pos->act_li = pos->start_li;
		pos->let_nb = 0;
	}
/*
	while (pos->let_nb > 0 && (pos->ans[pos->let_nb - 1] != '\n'))
	{
		pos->let_nb--;
		if (pos->act_co == 0)
		{
			pos->act_co = pos->max_co - 1;
			pos->act_li--;
		}
		else
			pos->act_co--;
	}
*/	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

int		nb_line(t_pos *pos)
{
	int i;
	int line;

	i = 0;
	line = 0;
	while (pos->ans[i])
	{
		if (pos->ans[i] == '\n' || i % pos->max_co - 1 == 0)
			line++;
		i++;
	}
	return (line);
}

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
	else
		pos->let_nb -= prev_act_co - pos->act_co + 1;
	pos->act_li--;
	if (pos->let_nb < 0)
	{
		pos->let_nb = 0;
		pos->act_co = 2;
	}
}

void		jump_down_with_backslash_n(t_pos *pos)
{
	int		new_let_nb;
	int		next_line_len;
	int		tmp_act_co;

	new_let_nb = 0;
	tmp_act_co = pos->act_co;
	next_line_len = 0;
	while (pos->ans[pos->let_nb] != '\n' && tmp_act_co < pos->max_co)
	{
		pos->let_nb++;
		tmp_act_co++;
	}
	pos->let_nb++;
	if (tmp_act_co == pos->max_co)
		tmp_act_co = 1;
	else
		tmp_act_co = 0;
	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != '\n' &&
			tmp_act_co < pos->max_co)
	{
		if (next_line_len == pos->act_co)
			new_let_nb = pos->let_nb;
		pos->let_nb++;
		next_line_len++;
		tmp_act_co++;
	}
	pos->act_li++;
	if (next_line_len > pos->act_co)
		pos->let_nb = new_let_nb;
	else
		pos->act_co =tmp_act_co;
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

void		jump_down(t_pos *pos)
{
	if (check_if_backslash_n(pos, pos->let_nb, 1) == 0)
	{
		if (pos->let_nb + pos->max_co > ft_strlen(pos->ans))
		{
			pos->act_co = ft_strlen(pos->ans) % pos->max_co + 2;
			if (pos->is_complete == 0)
				pos->act_co = ((ft_strlen(pos->ans) - pos->let_nb_saved) % pos->max_co) + 2;
			pos->let_nb = ft_strlen(pos->ans);
		}
		else
			pos->let_nb += pos->max_co;
		pos->act_li++;
	}
	else /*if (pos->is_complete == 1)*/
		jump_down_with_backslash_n(pos);
}

void	find_jump(char *buf, t_pos *pos)
{
	int	nb_line;
	int	j;

	nb_line = count_nb_line(pos, &j);
	if (ft_strcmp(buf + 2, "[A") == 0 && pos->act_li > pos->start_li)
		jump_up(pos);
	if (ft_strcmp(buf + 2, "[B") == 0 && (pos->start_li + nb_line) > pos->act_li)
		jump_down(pos);
	if (ft_strcmp(buf + 2, "[D") == 0)
		jump_left(pos);
	else if (ft_strcmp(buf + 2, "[C") == 0)
		jump_right(pos);
	else if (ft_strcmp(buf + 1, "[F") == 0)
		go_hard(pos);
	else if (ft_strcmp(buf + 1, "[H") == 0)
		or_go_home(pos);
}
