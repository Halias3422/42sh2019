/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   start_termcaps.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 16:11:39 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			print_prompt(t_pos *pos)
{
	t_var			*var;
	char			*state;

	state = NULL;
	var = stock(NULL, 6);
	if (var)
		state = ft_get_val("?", var, SPE);
	if (pos->ret == 1 && state && ft_strcmp(state, "0") != 0)
		ft_printf("{B.T.red.}%s{eoc}", pos->prompt);
	else
		print_second_prompt(pos);
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
	int			i;

	if (pos->active_heredoc)
	{
		i = ft_strlen(pos->ans) - 1;
		if (pos->ans[i] != '\n')
			return (0);
		heredoc_ctrl_d(pos, hist);
		ft_strdel(&pos->saved_ans);
		if (pos->active_heredoc == 0)
			return (1);
	}
	if (!pos->ans || !pos->ans[0])
	{
		free_job_list();
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
	if (pos->max_co > 2 && buf[0] != 4)
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
	char			*ans;
	unsigned char	buf[9];

	if (check_if_process_in_bg(pos, buf) == 1)
		return (pos->ans);
	while (hist && hist->next)
		hist = hist->next;
	ghist = &hist;
	init_terminfo(pos);
	ft_bzero(buf, 8);
	print_first_prompt(pos);
	init_pos(pos, 1);
	print_prompt(pos);
	signal_list();
	while (1)
	{
		if ((ans = termcaps42sh_loop(pos, &hist, var, buf)) != NULL)
			return (ans);
	}
	return (NULL);
}
