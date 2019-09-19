/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_list.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:06:47 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 14:19:53 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		free_replace(t_replace *replace)
{
	t_replace	*tmp;

	while (replace)
	{
		ft_strdel(&replace->name);
		tmp = replace;
		replace = replace->next;
		free(&tmp);
	}
}

void		init_replace(t_replace **replace)
{
	(*replace) = malloc(sizeof(t_replace));
	(*replace)->name = NULL;
	(*replace)->next = NULL;
}

void		*get_replace(void *stock, int i)
{
	static t_replace *ret;

	if (i == 1)
		ret = stock;
	if (i == 2)
		return (ret);
	return (NULL);
}
