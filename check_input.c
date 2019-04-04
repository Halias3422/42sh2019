/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 10:05:58 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 11:26:26 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		input_is_printable_char(t_pos *pos, char *buf)
{
	fill_char_ans(buf, pos);
	print_ans(pos);
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co + 1, pos->act_li),
			1, ft_putchar);
	if (pos->let_nb % pos->max_co == 0)
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->act_li + 1),
				1, ft_putchar);
	pos->tot_co++;
	pos->act_co++;
	check_poussin(buf[0]);
}

void		input_is_entry(t_pos *pos)
{
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_printf("\nreponse -> |%s|\n", pos->ans);
	write(pos->history, pos->ans, ft_strlen(pos->ans));
	write(pos->history, "\n", 1);
	close(pos->history);
	main();
}

void		input_is_backspace(t_pos *pos)
{
	if (pos->act_co > 0 || pos->act_li > pos->start_li)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		remove_char_ans(pos);
		pos->tot_co -= pos->tot_co == 0 ? 0 : 1;
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
		print_ans(pos);
	}
}

t_hist		*check_input(char *buf, t_pos *pos, t_hist *hist)
{
	if (buf[1])
		hist = find_arrow(buf, pos, hist);
	else
	{
		if (buf[0] == 127)
			input_is_backspace(pos);
		else if (buf[0] == 10)
			input_is_entry(pos);
		else
			input_is_printable_char(pos, buf);
	}
	return (hist);
}
