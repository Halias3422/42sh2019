/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_ans.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 10:37:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 11:36:02 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		remove_char_ans(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->let_nb);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb - 1);
	if (pos->let_nb < (int)ft_strlen(pos->ans))
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 0);
	pos->ans = swap;
	pos->let_nb--;
	pos->mode = 1;
//	tputs(tgoto(tgetstr("cm", NULL), pos->act_co - 1, pos->act_li), 1,
//			ft_putchar);
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_co = pos->max_co;
		pos->act_li--;
		pos->mode = 0;
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
				1, ft_putchar);
	}

//	print_ans(pos);
//	tputs(tgetstr("sc", NULL), 1, ft_putchar);

//	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void		fill_char_ans(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	pos->let_nb = pos->act_co;
	if (pos->act_li > pos->start_li)
		pos->let_nb = ((pos->act_li - pos->start_li) * pos->max_co)
			+ pos->act_co;
	if (pos->let_nb == (int)ft_strlen(pos->ans))
	{
		pos->ans = ft_strjoinf(pos->ans, buf, 0);
	}
	else
	{
		swap = ft_strnew(pos->let_nb + 1);
		swap = ft_strncpy(swap, pos->ans, pos->let_nb);
		swap = ft_strjoinf(swap, buf, 0);
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 0);
		pos->ans = swap;
	}
	pos->let_nb++;
}

void		print_ans(t_pos *pos)
{
	int		len_ans;
	int		nb_li;

	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	len_ans = ft_strlen(pos->ans);
	clean_screen(pos);
	write(1, pos->ans, len_ans);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	nb_li = len_ans / pos->max_co;
	while (nb_li != 0)
	{
		if (pos->act_li < pos->max_li && pos->act_co == pos->max_co)
		{
			pos->act_li++;
			pos->act_co = 0;
		}
		else if (pos->act_co == pos->max_co && pos->act_li == pos->max_li)
		{
			pos->start_li--;
			pos->act_co = 0;
		}
		nb_li--;
		if (pos->tot_li < pos->act_li)
			pos->tot_li = pos->act_li;
	}
}
