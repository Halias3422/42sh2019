/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 14:41:17 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 16:20:55 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		remove_char_ans(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->let_nb);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb - 1);
	if (pos->let_nb < pos->len_ans)
	{
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 1);
		free(pos->ans);
	}
	pos->ans = swap;
	pos->let_nb--;
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_co = pos->max_co;
		pos->act_li--;
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
				1, ft_putchar);
	}
}

void		input_is_backspace(t_pos *pos)
{
	if (pos->let_nb > 0 && pos->ans[pos->let_nb - 1] == '\n')
	{
		pos->act_li -= 1;
		pos->act_co = len_of_previous_line(pos);
		pos->len_ans -= 1;
		remove_char_ans(pos);
	}
	else if ((pos->let_nb > 0 && (pos->act_co > pos->len_prompt || pos->ans[pos->let_nb - 1] != '\n')))
	{
		remove_char_ans(pos);
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
		pos->len_ans -= 1;
	}
}

t_hist		*check_input(char *buf, t_pos *pos, t_hist *hist, t_inter *inter)
{
	(void)inter;
	if (buf[0] == 27)
		escape_code(buf, pos, hist);
	else
	{
		bzero(buf + 1, 3);
		if (buf[0] == 127)
			input_is_backspace(pos);
		else if (buf[0] == 10)
			return (hist);
		else
			input_is_printable_char(pos, buf);
	}
	clean_screen(pos);
	print_ans(pos, buf);
	return (hist);
}
