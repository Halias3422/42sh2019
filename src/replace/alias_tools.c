/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/12 12:34:55 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 10:10:44 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

char		check_last_char(t_alias *alias, int j)
{
	int		i;

	i = 0;
	while (j > 1)
	{
		alias = alias->next;
		j--;
	}
	while (alias->data[i])
		i++;
	return (alias->data[i - 1]);
}

void		fill_list(char *str, t_alias *alias)
{
	ft_strdel(&alias->data);
	alias->data = ft_strdup(str);
}

void		free_array(char ***array)
{
	int		i;

	i = 0;
	while ((*array)[i])
	{
		ft_strdel(&(*array)[i]);
		i++;
	}
}

int			end(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i + 1);
}
