/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:15:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/15 07:10:06 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	clean_at_start(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL),
		pos->start_co, pos->start_li), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL),
		pos->start_co, pos->start_li), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}

void	short_update(t_pos *pos, int len)
{
	pos->act_li = pos->start_li + len / pos->max_co;
	pos->act_co = len % pos->max_co;
	while (pos->act_li > pos->max_li)
	{
		pos->act_li -= 1;
		prompt_is_on_last_char(pos);
	}
}

void	update_position(t_pos *pos)
{
	int		get_len;

	get_len = get_len_with_lines(pos);
	short_update(pos, get_len);
	pos->let_nb = ft_strlen(pos->ans);
	pos->len_ans = pos->let_nb;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}
