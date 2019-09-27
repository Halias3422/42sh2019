/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 10:02:36 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 08:29:17 by bjuarez     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static int		verif_token_check(char *str, int i)
{
	if (ft_strncmp(&str[i], "&&", 2) == 0)
		return (1);
	if (ft_strncmp(&str[i], "||", 2) == 0)
		return (2);
	if (ft_strncmp(&str[i], "|", 1) == 0)
		return (3);
	return (0);
}

static int		verif_double_token(t_pos *pos, int i)
{
	int			nb;

	while (pos->ans && pos->ans[i] != '\0')
	{
		nb = 0;
		if (verif_token_check(pos->ans, i) > 0)
		{
			if (pos->ans[i + 1] == '\0' || pos->ans[i + 2] == '\0')
				break ;
			i += 2;
			while (pos->ans[i] && verif_token_check(pos->ans, i) == 0)
			{
				if (pos->ans[i] && pos->ans[i] > 32 && pos->ans[i] <= 126)
					nb++;
				if (pos->ans[i] != '\0')
					i++;
			}
			if (nb == 0)
				return (1);
		}
		if (pos->ans[i] != '\0')
			i++;
	}
	return (0);
}

int				check_in_2(t_pos *pos)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (pos->ans[i] > 32 && pos->ans[i] < 127)
		{
			if (nb == 0 && verif_token_check(pos->ans, i) > 0)
				return (1);
			nb++;
		}
		i++;
	}
	if (verif_double_token(pos, 0) == 1)
		return (1);
	if (pos->is_complete == 1)
		return (1);
	return (0);
}

int				check_in_3(t_pos *pos)
{
	int			i;
	int			check;

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
