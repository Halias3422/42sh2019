/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_cnt.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/12 07:08:58 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 07:12:28 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

int			cnt_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			cnt_list(t_alias *alias)
{
	int		nb;

	nb = 0;
	while (alias)
	{
		alias = alias->next;
		nb++;
	}
	return (nb);
}
