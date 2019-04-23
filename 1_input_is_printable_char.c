/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_printable_char.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 10:18:07 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 13:22:48 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void	if_prompt_is_on_last_char(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co + 1, pos->max_li + 1), 1, ft_putchar);
	write(1, " ", 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if (pos->act_co != pos->max_co - 1)
	{
		pos->act_co += 1;
		pos->act_li -= 1;
	}
	else
		pos->act_co = 0;
	pos->start_li -= 1;
}

int			count_nb_line(t_pos *pos, int *j)
{
	int		nb_line;
	int		i;

	nb_line = 0;
	i = 0;
	while (pos->ans[i])
	{
		if (pos->ans[i] == '\n')
		{
			nb_line += 1;
			*j = 2;
		}
		else if (*j % pos->max_co/* - (*j > pos->max_co ? 0 : 2)))*/ == 0 && *j != 0)
			nb_line += 1;
		++*j;
		i++;
	}
	--*j;
	return (nb_line);
}

void		input_is_printable_char(t_pos *pos, char *buf)
{
	int		nb_char_last_line;

	nb_char_last_line = 0;

	pos->history_mode = 1;
	fill_char_ans(buf, pos);
	pos->len_ans = pos->len_prompt + ft_strlen(pos->ans);
	if (pos->act_li != pos->max_li && pos->act_co == pos->max_co - 1)
	{
		pos->act_co = 0;
		if (pos->act_li == pos->max_li)
			pos->start_li -= 1;
		else
			pos->act_li += 1;
	}
	else if (pos->is_complete == 1 && ((pos->start_li + (pos->len_ans / pos->max_co)) == pos->max_li + 1 && pos->len_ans % (pos->max_co) == 0))
	{
		pos->history_mode = 51;
		if_prompt_is_on_last_char(pos);
	}
	else if (pos->is_complete == 0 && pos->start_li + (pos->debug = count_nb_line(pos, &nb_char_last_line)) == pos->max_li + 1 && nb_char_last_line % pos->max_co == 0)/*(pos->act_co == pos->max_co - 1 && pos->act_li == pos->max_li))*/
	{
		pos->history_mode = 15;
		if_prompt_is_on_last_char(pos);
	}
	else
		pos->act_co += 1;
	pos->let_nb += 1;
}
