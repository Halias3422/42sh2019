/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_ans.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 12:37:34 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 15:22:49 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		print_ans(t_pos *pos)
{
	write(1, pos->ans, ft_strlen(pos->ans));
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		fill_char_ans(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	if (pos->let_nb == (int)ft_strlen(pos->ans))
		pos->ans = ft_strjoinf(pos->ans, buf, 1);
	else
	{
		swap = ft_strnew(pos->let_nb + 1);
		swap = ft_strncpy(swap, pos->ans, pos->let_nb);
		swap = ft_strjoinf(swap, buf, 1);
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 1);
		free(pos->ans);
		pos->ans = swap;
	}
}
