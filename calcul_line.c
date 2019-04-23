/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calcul_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:46:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 16:02:43 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int                     len_of_previous_line(t_pos *pos)
{
	int             len;
	int             i;

	i = pos->let_nb - 2;
	len = 0;
	while (pos->ans[i] > 0 && pos->ans[i] != '\n')
	{
		i--;
		len++;
	}
	if (pos->act_li == pos->start_li)
		len += pos->len_prompt;
	return (len);
}
