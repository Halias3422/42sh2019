/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calcul_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:46:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 08:49:32 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int			get_len_with_lines(t_pos *pos)
{
	int		i;
	int		len;
	int		line;

	line = pos->len_prompt;
	i = -1;
	len = pos->len_prompt;
	while (pos->ans[++i])
	{
		if (pos->ans[i] == '\n')
		{
			if (line < pos->max_co)
				len += (pos->max_co - line);
			else
				len += (pos->max_co - line % pos->max_co);
			line = 0;
		}
		else
		{
			line += 1;
			len += 1;
		}
	}
	return (len);
}

int			len_of_previous_line(t_pos *pos)
{
	int		len;
	int		i;

	i = pos->let_nb - 2;
	len = 0;
	while (i >= 0 && pos->ans[i] != '\n')
	{
		i--;
		len++;
	}
	if (pos->act_li == pos->start_li)
		len += pos->len_prompt;
	if (len > pos->max_co)
		len = len % pos->max_co;
	return (len);
}
