/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   termcaps_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 12:07:48 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 01:13:16 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void	print_info(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 0), 1, ft_putchar);
	printf(" act_co    = %03d/\n", pos->act_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 1), 1, ft_putchar);
	printf(" act_li    = %03d/\n", pos->act_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 2), 1, ft_putchar);
	printf(" start_co  = %03d/\n", pos->start_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 3), 1, ft_putchar);
	printf(" start_li  = %03d/\n", pos->start_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 4), 1, ft_putchar);
	printf(" max_co    = %03d/\n", pos->max_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 5), 1, ft_putchar);
	printf(" max_li    = %03d/\n", pos->max_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 6), 1, ft_putchar);
	printf(" let_nb    = %03d/\n", pos->let_nb);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 7), 1, ft_putchar);
	printf(" strlen_ans= %03zu/\n", ft_strlen(pos->ans));
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 8), 1, ft_putchar);
	printf(" len_ans   = %03d/\n", pos->len_ans);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 9), 1, ft_putchar);
	printf(" debug     = %03d/\n", pos->debug);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void	print_hist(t_pos *pos, t_hist *hist)
{
	t_hist	*tmp;
	int		i;

	tmp = hist;
	i = 0;
	while (tmp->prev)
		tmp = tmp->prev;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (tmp)
	{
		tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 65, i), 1, ft_putchar);
		printf(" cmd[%d]    = %10s/\n", i, tmp == NULL ? NULL : tmp->cmd);
		i++;
		tmp = tmp->next;
	}
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void	clean_screen(t_pos *pos)
{
//	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

int poussin = 0;

void	check_poussin(char c)
{
	if (poussin == 0 && c == 'e')
		poussin = 1;
	else if (poussin == 1 && c == 'x')
		poussin = 2;
	else if (poussin == 2 && c == 'i')
		poussin = 3;
	else if (poussin == 3 && c == 't')
	{
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		exit(0);
	}
	else
		poussin = 0;
}
