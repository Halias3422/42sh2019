/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_list.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/15 05:49:46 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/15 05:51:04 by mdelarbr    ###    #+. /#+    ###.fr     */
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
	(*replace)->name = ft_strdup("");
	(*replace)->next = NULL;
}
