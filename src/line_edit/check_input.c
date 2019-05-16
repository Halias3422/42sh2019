/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 14:41:17 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 07:50:53 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static void		update_history(t_pos *pos, t_hist *hist, char *buf)
{
	ft_strdel(&pos->saved_ans);
	if (buf[0] != 10)
		pos->saved_ans = ft_strdup(pos->ans);
	if (hist && hist->next == NULL)
	{
		if (hist->cmd != NULL)
			ft_strdel(&hist->cmd);
		hist->cmd = ft_strdup(pos->ans);
	}
	if (pos->ans[0] == '\0' || (pos->is_complete == 0 && pos->let_nb > 0 &&
				pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt))
		pos->history_mode = 0;
}

t_hist			*check_input(unsigned char *buf, t_pos *pos, t_hist *hist)
{
/*	ft_printf("buf[0] = %d, %c\n", buf[0], buf[0]);
	ft_printf("buf[1] = %d, %c\n", buf[1], buf[1]);
	ft_printf("buf[2] = %d, %c\n", buf[2], buf[2]);
	ft_printf("buf[3] = %d, %c\n", buf[3], buf[3]);
	exit (0);
*/	pos->debug = pos->ctrl_search_history;
	selection_check(pos, (char*)buf);
//	if (check_copy(buf, pos) == 0)
	if (buf[0] == 27)
		hist = escape_code((char*)buf, pos, hist);
	else
	{
		if (buf[0] == 9 && pos->is_complete == 1)
			input_is_tab(pos);
		else if (buf[0] == 127)
			pos->ans_printed = input_is_backspace(pos);
		else if (pos->ctrl_search_history == 0 && buf[0] == 10)
			hist = input_is_entry(pos, hist, (char*)buf);
		else if (buf [0] != 18 && buf[0] != 127 && buf[0] != 10 && buf[0] != 9)
			input_is_printable_char(pos, (char*)buf);
		if (buf[0] == 18 || pos->ctrl_search_history == 1)
			hist = control_search_history(pos, hist, buf);
		update_history(pos, hist, (char*)buf);
	}
	if (buf[0] != 10 && pos->ans_printed == 0)
		prepare_to_print(pos, (char*)buf);
	pos->ans_printed = 0;
	pos->navigation -= 1;
	return (hist);
}
