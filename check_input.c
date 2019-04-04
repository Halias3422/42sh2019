/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 12:30:53 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 15:57:40 by rlegendr    ###    #+. /#+    ###.fr     */
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
	if (pos->act_co == pos->max_co)
	{
		pos->act_co = 1;
		if (pos->act_li == pos->max_li)
			pos->start_li -= 1;
		else
			pos->act_li += 1;
	}
	else
		pos->act_co += 1;
	pos->let_nb += 1;
	check_poussin(buf[0]);
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
			;
		else
		{
			if (buf[0] == 10)
				input_is_entry(pos);
			else
				input_is_printable_char(pos, buf);
			print_ans(pos);
		}
	}
	return (hist);
}
