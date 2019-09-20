/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   start_termcaps.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 14:31:04 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			print_prompt(t_pos *pos)
{
	ft_printf("{B.T.cyan.}%s{eoc}", pos->prompt);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

static int		start_termcaps(t_pos *pos, char *buf)
{
	int				ret;

	init_terminfo(pos);
	ret = check_term();
	if (ret == -1)
		exit(0);
	init_pos(pos);
	ft_bzero(buf, 8);
	return (ret);
}

static char		*returning_ans(t_pos *pos)
{
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	write(1, "\n", 1);
	return (pos->ans);
}

static char		*termcaps42sh_loop(t_pos *pos, t_hist **hist, t_var *var,
				unsigned char buf[9])
{
	int				ret;

	ret = read(0, buf, 1);
	if (ret > 0 && buf[0] == 137)
		return (NULL);
	if (buf[0] == 27 || buf[0] == 226 || buf[0] == 195)
		ret = read(0, buf + 1, 8);
	else if (buf[0] == 4)
	{
		if (!pos->ans || !pos->ans[0])
		{
			write_alias(var, pos);
			exit(0);
		}
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
	unsigned char	buf[9];
	char			*ans;

	while (hist->next)
		hist = hist->next;
	ghist = &hist;
	start_termcaps(pos, (char*)buf);
	print_prompt(pos);
	signal_list();
	while (1)
	{
		if ((ans = termcaps42sh_loop(pos, &hist, var, buf)) != NULL)
			return (ans);
	}
	return (NULL);
}
