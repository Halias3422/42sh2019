/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_printable_char.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 10:18:07 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 16:04:04 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

static void	if_prompt_is_on_last_char(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co + 1, pos->max_li + 1), 1, ft_putchar);
	write(1, " ", 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	pos->debug++;
	if (pos->act_co != pos->max_co - 1)
	{
		pos->act_co += 1;
		pos->act_li -= 1;
	}
	else
		pos->act_co = 0;
	pos->start_li -= 1;
}

void		input_is_printable_char(t_pos *pos, char *buf)
{
	pos->history_mode = 1;
	fill_char_ans(buf, pos);
	pos->len_ans += 1;
	if (pos->act_li != pos->max_li && pos->act_co == pos->max_co - 1)
	{
		pos->act_co = 0;
		if (pos->act_li == pos->max_li)
			pos->start_li -= 1;
		else
			pos->act_li += 1;
	}
	else if ((pos->start_li + (pos->len_ans / pos->max_co)) == pos->max_li + 1 && pos->len_ans % (pos->max_co) == 0)
		if_prompt_is_on_last_char(pos);
	else
		pos->act_co += 1;
	pos->let_nb += 1;
//	check_poussin(buf[0]);
}
