/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_ans.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 10:37:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 11:13:05 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void	remove_char_ans(t_pos *pos)
{
	char	*swap;
	if (pos->act_co > 0)
	{
		swap = ft_strnew(pos->act_co);
		swap = ft_strncpy(swap, pos->ans, pos->act_co - 1);
		if (pos->act_co < pos->tot_co)
			swap = ft_strjoinf(swap, pos->ans + pos->act_co, 0);
		//	free(pos->ans);
		pos->ans = swap;
		pos->let_nb--;
	}
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
//		swap = ft_strnew(pos->act_co);
//		swap = ft_strncpy(swap, pos->ans, pos->act_co - 1);
		pos->act_co = pos->max_co + 1;
		pos->act_li--;
	}
}

void	fill_char_ans(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	pos->let_nb = pos->act_co;
	if (pos->act_li > pos->start_li)
		pos->let_nb = ((pos->act_li - pos->start_li) * pos->max_co) + pos->act_co;
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

void	print_ans(t_pos *pos)
{
	int		len_ans;
	int		nb_li;

	len_ans = ft_strlen(pos->ans);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li), 1, ft_putchar);

	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(tgetstr("cb", NULL), 1, ft_putchar);
	write(1, pos->ans, len_ans);
	nb_li = len_ans / pos->max_co;
	while (nb_li != 0)
	{
		if (pos->act_li < pos->max_li && pos->act_co == pos->max_co)
		{
			pos->act_li++;
			pos->act_co = 0;
		}
		else if (pos->act_co == pos->max_co)
		{
			pos->start_li--;
			pos->act_co = 0;
		}
		nb_li--;
		if (pos->tot_li < pos->act_li)
			pos->tot_li = pos->act_li;
	}
}
