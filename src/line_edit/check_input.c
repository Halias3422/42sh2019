/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 14:41:17 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/09 17:14:37 by mjalenqu    ###    #+. /#+    ###.fr     */
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

static void		print_ecran(t_pos *pos)
{
	char *pwd;

	ft_printf("\n{T.cyan.}42sh {eoc}{B.}--- {B.T.yellow.}%s{eoc}\n", pwd = getcwd(NULL, 1000));
	ft_printf("{B.T.cyan.}%s{eoc}%s ", pos->prompt, pos->ans);
	pos->let_nb = ft_strlen(pos->ans);
	ft_strdel(&pwd);
}

static void		clear_all(t_pos *pos)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar);
	print_ecran(pos);
	get_cursor_info(pos, &pos->start_li, &pos->start_co, 0);
	update_position(pos);
}

static t_hist	*input_no_escape(t_pos *pos, t_hist *hist, unsigned char *buf)
{
	if (buf[0] == 9 && pos->is_complete == 1 && pos->ctrl_search_history == 0)
		input_is_tab(pos);
	else if (buf[0] == 127)
		pos->ans_printed = input_is_backspace(pos);
	else if (buf[0] == 10 && pos->ctrl_search_history == 0)
		hist = input_is_entry(pos, hist, (char*)buf);
	else if (buf[0] != 127 && buf[0] != 10 && buf[0] != 9 && buf[0] != 18 && buf[0] != 12)
		input_is_printable_char(pos, (char*)buf);
	if (buf[0] == 18 || pos->ctrl_search_history == 1)
		hist = control_search_history(pos, hist, buf);
	if (buf[0] == 12)
		clear_all(pos);
	if (pos->ans != NULL)
		update_history(pos, hist, (char*)buf);
	return (hist);
}

t_hist			*check_input(unsigned char *buf, t_pos *pos, t_hist *hist)
{
	if (buf[0] != 226 && buf[0] != 195)
		selection_check(pos, (char*)buf);
	if (buf[0] == 27)
		hist = escape_code((char*)buf, pos, hist);
	else if (buf[0] == 226 || buf[0] == 195)
		check_copy(buf, pos);
	else
		hist = input_no_escape(pos, hist, buf);
	if (buf[0] != 10 && pos->ans_printed == 0)
		prepare_to_print(pos, (char*)buf);
	pos->ans_printed = 0;
	return (hist);
}
