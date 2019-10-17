/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_prompt.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 11:35:06 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 13:58:11 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void		print_first_prompt(t_pos *pos)
{
	if (pos->shtheme == 5)
		ft_printf("\n42sh --- %s\n",
				pos->pwd);
	else if (pos->shtheme == 4)
		ft_printf("\n{B.T.yellow.}42sh {eoc}{B.}--- {T.cyan.}%s{eoc}\n",
				pos->pwd);
	else if (pos->shtheme == 3)
		ft_printf("\n{T.purple.}42sh {eoc}{B.}--- {T.grey.}%s{eoc}\n",
				pos->pwd);
	else if (pos->shtheme == 2)
		ft_printf("\n{B.T.green.}42sh {eoc}{B.}--- {T.blue.}%s{eoc}\n",
				pos->pwd);
	else if (pos->shtheme == 1)
		ft_printf("\n{B.T.cyan.}42sh {eoc}{B.}--- {T.yellow.}%s{eoc}\n",
				pos->pwd);
}

void					print_second_prompt(t_pos *pos)
{
	if (pos->shtheme == 5)
		ft_printf("%s", pos->prompt);
	else if (pos->shtheme == 4)
		ft_printf("{B.T.green.}%s{eoc}", pos->prompt);
	else if (pos->shtheme == 3)
		ft_printf("{T.purple.}%s{eoc}", pos->prompt);
	else if (pos->shtheme == 2)
		ft_printf("{B.T.green.}%s{eoc}", pos->prompt);
	else if (pos->shtheme == 1)
		ft_printf("{B.T.cyan.}%s{eoc}", pos->prompt);
}
