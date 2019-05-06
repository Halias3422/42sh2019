/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 14:41:17 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 15:34:36 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static void		update_history(t_pos *pos, t_hist *hist, char *buf)
{
	pos->saved_ans = ft_secure_free(pos->saved_ans);
	if (buf[0] != 10)
		pos->saved_ans = ft_strdup(pos->ans);
	if (hist && hist->next == NULL)
	{
		if (hist->cmd != NULL)
			hist->cmd = ft_secure_free(hist->cmd);
		hist->cmd = ft_strdup(pos->ans);
	}
	if (pos->ans[0] == '\0' || (pos->is_complete == 0 && pos->let_nb > 0 &&
				pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt))
		pos->history_mode = 0;
}

t_hist			*check_input(char *buf, t_pos *pos, t_hist *hist)
{
	selection_check(pos, buf);
	if (buf[0] == 27)
		hist = escape_code(buf, pos, hist);
	else
	{
		if (buf[0] == 9)
			input_is_tab(pos);
		else if (buf[0] == 127)
			pos->ans_printed = input_is_backspace(pos);
		else if (buf[0] == 10)
			hist = input_is_entry(pos, hist, buf);
		else if (buf[0] != 127 && buf[0] != 10)
			input_is_printable_char(pos, buf);
		update_history(pos, hist, buf);
	}
	if (buf[0] != 10 && pos->ans_printed == 0)
		prepare_to_print(pos, buf);
	pos->ans_printed = 0;
	return (hist);
}
