/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bjuarez <bjuarez@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 10:52:21 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 11:38:19 by bjuarez     ###    #+. /#+    ###.fr     */
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
		ft_printf
		("\n42sh: syntax {T.red.B.}error{eoc} near unexpected token `${'\n");
		return (1);
	}
	if (pos->is_complete == 1)
		return (1);
	return (0);
}


