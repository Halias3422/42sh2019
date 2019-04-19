/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_ans.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 12:37:34 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 10:47:52 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		remove_char_ans(t_pos *pos)
{
	char	*swap;

	swap = NULL;
	swap = ft_strnew(pos->let_nb);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb - 1);
	if (pos->let_nb < pos->len_ans)
	{
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 1);
		free(pos->ans);
	}
	pos->ans = swap;
	pos->let_nb--;
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_co = pos->max_co;
		pos->act_li--;
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
				1, ft_putchar);
	}
}

int			get_last_line(t_pos *pos)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	i = ft_strlen(pos->ans) - 1;
	k = ft_strlen(pos->ans) - 1;
	while (pos->ans[i] != '\n')
		i--;
	while (pos->ans + k != pos->ans + i && j % pos->max_co != 0)
	{
		j++;
		k--;
	}
	if (j % pos->max_co == 0)
		return (j + 1);
	return (i + 1);
}

void		print_ans(t_pos *pos, char *buf)
{
	int		i;
	int		line;

	line = 0;
	i = -1;
	(void)buf;
/*	if (pos->is_complete == 1)
	{
*/		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li),
				1, ft_putchar);
		if (ft_strchr(pos->ans, '\n') == NULL)
			write(1, pos->ans, ft_strlen(pos->ans));
		else
		{
			while (pos->ans[++i])
			{
			write(1, &pos->ans[i], 1);
			if (pos->ans[i] == '\n')// && buf[0] == 10)
				write(1, "> ", 2);
		//	ft_printf("line = |%d| - pos->ans[%d] = |%d|\n", line, i, pos->ans[i]);
			if (line == pos->max_co - 2 && pos->ans[i] == '\n')
			{
				write(1, "\n", 1);
			}
			if (i == pos->max_co)
				line = 0;
			line++;
			}
		}
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
				1, ft_putchar);
/*	}
	else
	{
		tputs(tgoto(tgetstr("cm", NULL), pos->len_prompt, pos->act_li),
				1, ft_putchar);
		write(1, pos->ans + get_last_line(pos), ft_strlen(pos->ans + get_last_line(pos)));
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
				1, ft_putchar);
	}
*/}


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
