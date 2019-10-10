/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   start_termcaps.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 13:01:24 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			print_prompt(t_pos *pos)
{
	ft_printf("{B.T.cyan.}%s{eoc}", pos->prompt);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

static char		*returning_ans(t_pos *pos)
{
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	write(1, "\n", 1);
	return (pos->ans);
}

static int		handle_ctrl_d(t_pos *pos, t_hist **hist, t_var *var)
{
	if (pos->active_heredoc)
	{
		heredoc_ctrl_d(pos, hist);
		if (pos->active_heredoc == 0)
			return (1);
	}
	if (!pos->ans || !pos->ans[0])
	{
		write_alias(var, pos);
		exit(0);
	}
	return (0);
}

static char		*termcaps42sh_loop(t_pos *pos, t_hist **hist, t_var *var,
				unsigned char buf[9])
{
	read(0, buf, 1);
	if (buf[0] == 137)
		return (NULL);
	if (buf[0] == 27 || buf[0] == 226 || buf[0] == 195)
		read(0, buf + 1, 8);
	else if (buf[0] == 4)
	{
		if (handle_ctrl_d(pos, hist, var) == 1)
			return (returning_ans(pos));
	}
	if (pos->max_co > 2)
		*hist = check_input(buf, pos, *hist);
	if (buf[0] == 10 && pos->is_complete == 1 && pos->replace_hist == 0)
	{
		stock(*hist, 7);
		return (returning_ans(pos));
	}
	pos->replace_hist = 0;
	ft_bzero(buf, 8);
	return (NULL);
}

char			*termcaps42sh(t_pos *pos, t_hist *hist, t_var *var)
{
	char			*pwd;
	unsigned char	buf[9];
	char			*ans;

	if (pos->last_cmd_on_bg == 1)
	{
		pos->last_cmd_on_bg = 0;
		return (ft_strdup("\n"));
	}
	while (hist && hist->next)
		hist = hist->next;
	ghist = &hist;
	init_terminfo(pos);
	ft_bzero(buf, 8);
	ft_printf("\n{B.T.cyan.}42sh {eoc}{B.}--- {B.T.yellow.}%s{eoc}\n",
		pwd = print_pwd(var));
	ft_strdel(&pwd);
	init_pos(pos);
	print_prompt(pos);
	signal_list();
	while (1)
	{
		if ((ans = termcaps42sh_loop(pos, &hist, var, buf)) != NULL)
			return (ans);
	}
	return (NULL);
}
