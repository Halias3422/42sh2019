/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 10:02:36 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 07:21:55 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int		check_in_2(t_pos *pos)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (pos->ans[i] > 32 && pos->ans[i] < 127)
		{
			if (nb == 0 && verif_token(&pos->ans[i]) > 0)
				return (1);
			nb++;
		}
		i++;
	}
	if (pos->is_complete == 1)
		return (1);
	return (0);
}

int		check_in_3(t_pos *pos)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (ft_strncmp(&pos->ans[i], "${", 2) == 0)
			check++;
		if (check > 0 && ft_strncmp(&pos->ans[i], "}", 1) == 0)
			check--;
		i++;
	}
	if (check > 0)
	{
		pos->error = 2;
		ft_printf_err("\n42sh: syntax {T.red.B.}error{eoc} ");
		ft_printf_err("near unexpected token `${'\n");
		return (1);
	}
	if (pos->is_complete == 1)
		return (1);
	return (0);
}
