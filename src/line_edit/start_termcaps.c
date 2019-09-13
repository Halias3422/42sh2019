/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   start_termcaps.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 08:44:34 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static void		write_alias(t_var *var, t_pos *p)
{
	chdir(p->path);
	p->alias = open("./.aliases", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	while (var)
	{
		if (var->type == 2)
		{
			write(p->alias, var->name, ft_strlen(var->name));
			write(p->alias, "=", 1);
			write(p->alias, var->data, ft_strlen(var->data));
			write(p->alias, "\n", 1);
		}
		var = var->next;
	}
}

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
	tputs(tgoto(tgetstr("cm", NULL),
	pos->act_co, pos->act_li), 1, ft_putchar);
	write(1, "\n", 1);
	return (pos->ans);
}

char			*termcaps42sh(t_pos *pos, t_hist *hist, t_var *var)
{
	int				ret;
	unsigned char	buf[9];

	while (hist->next)
		hist = hist->next;
	ghist = &hist;
	start_termcaps(pos, (char*)buf);
	print_prompt(pos);
	signal_list();
	while (1)
	{
		ret = read(0, buf, 1);
		if (buf[0] == 137)
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
			hist = check_input(buf, pos, hist);
		if (buf[0] == 10 && pos->is_complete == 1 && pos->replace_hist == 0)
		{
			stock(hist, 7);
			return (returning_ans(pos));
		}
		pos->replace_hist = 0;
		ft_bzero(buf, 8);
	}
	return (NULL);
}
