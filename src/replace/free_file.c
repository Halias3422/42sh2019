/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_file.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/09 07:30:29 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/09 09:31:45 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/alias.h"

void		free_list(t_alias *alias)
{
	t_alias		*tmp;

	while (alias)
	{
		ft_strdel(&alias->data);
		if (alias->prev)
			free(alias->prev);
		tmp = alias;
		alias = alias->next;
		free(tmp);
	}
}

void		free_ar(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
}

void		free_all_the_ar(char ***array)
{
	int		i;

	i = 0;
	while ((*array)[i] != 0)
	{
		printf("%d -> %p\n", i, (*array)[i]);
		ft_strdel(&(*array)[i]);
		i++;
	}
	free(*array);
	free(array);
}
