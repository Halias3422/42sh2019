/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 12:30:53 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 12:47:05 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		input_is_entry(t_pos *pos)
{
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_printf("\nreponse -> |%s|\n", pos->ans);
	write(pos->history, pos->ans, ft_strlen(pos->ans));
	write(pos->history, "\n", 1);
	close(pos->history);
	main();
}

void		input_is_printable_char(t_pos *pos, char *buf)
{
	fill_char_ans(buf, pos);
	if (pos->act_li != pos->max_li && pos->act_co == pos->max_co - 1)
	{
		pos->act_co = 0;
		if (pos->act_li == pos->max_li)
			pos->start_li -= 1;
		else
			pos->act_li += 1;
	}
	else if (pos->act_li == pos->max_li && pos->act_co == pos->max_co)
	{
		write(1, "\n", 1);
		pos->act_co = 0;
		pos->start_li -= 1;
	}
	else
		pos->act_co += 1;
	pos->let_nb += 1;
	check_poussin(buf[0]);
}

void		input_is_backspace(t_pos *pos)
{
	if (pos->act_co > 0 || pos->act_li > pos->start_li)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		remove_char_ans(pos);
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
//		print_ans(pos);
	}
}

t_hist		*check_input(char *buf, t_pos *pos, t_hist *hist)
{
	//	if (buf[1])
	//		hist = find_arrow(buf, pos, hist);
	//	else
	//	{
	//		if (buf[0] == 127)
	//			input_is_backspace(pos);
	//		else if (buf[0] == 10)
	//			input_is_entry(pos);
	//		else
	if (buf[0] == 27)
		hist = find_arrow(buf, pos, hist);
	else
	{
		clean_screen(pos);
		if (buf[0] == 127)
			input_is_backspace(pos);
		else
		{
			if (buf[0] == 10)
				input_is_entry(pos);
			else
				input_is_printable_char(pos, buf);
		}
		print_ans(pos);
	}
	return (hist);
}
