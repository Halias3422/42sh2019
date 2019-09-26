/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 10:02:36 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/25 14:06:59 by bjuarez     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int		verif_token_check(char *str, int i)
{
	if (ft_strncmp(&str[i], "&&", 2) == 0)
		return (1);
	if (ft_strncmp(&str[i], "||", 2) == 0)
		return (2);
	if (ft_strncmp(&str[i], "|", 1) == 0)
		return (3);
	return (0);
}

int		verif_double_token(t_pos *pos)
{
	int i;
	int nb;
	int nb_token;

	nb_token = 0;
	i = 0;
	nb = 0;
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (verif_token_check(pos->ans, i) > 0)
		{
			i += 2;
			while (pos->ans && pos->ans[i] != '\0')
			{
				if (pos->ans[i] > 32 && pos->ans[i] < 127)
					nb++;
				if (nb == 1 && verif_token_check(pos->ans, i) > 0)
					return (1);
				else
					break ;
				/*if (verif_token_check(pos->ans, i) > 0)
				{
					ft_printf("Token = <%s>\n", &pos->ans[i]);
					nb_token++;
					i++;
				}
				ft_printf("passe par la + pos->ans = <%s>\n", &pos->ans[i]);
				if (nb_token == 2)
					break ;*/
				//else if (nb > 1 && verif_token_check(pos->ans, i - 1) > 0)
				//	break ;
				if (pos->ans[i] != '\0')
					i++;
			}
			nb = 0;
			nb_token = 0;
		}
		if (pos->ans[i] != '\0')
			i++;
	}
	return (0);
}

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
			if (nb == 0 && verif_token_check(pos->ans, i) > 0)
				return (1);
			nb++;
		}
		i++;
	}
	if (verif_double_token(pos) == 1)
		return (1);
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
