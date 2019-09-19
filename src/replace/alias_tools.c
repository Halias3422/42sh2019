/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 17:32:27 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 14:59:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

char	check_last_char(t_alias *alias, int j)
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

void	fill_list(char *str, t_alias *alias)
{
	ft_strdel(&alias->data);
	alias->data = ft_strdup(str);
}

void	free_array(char ***array)
{
	int		i;

	i = 0;
	while ((*array)[i])
	{
		ft_strdel(&(*array)[i]);
		i++;
	}
}

int		end(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i + 1);
}

void	replace_alias_while_fill(char *tmp, int *j, int *i, t_alias *alias)
{
	int		t;
	int		s;

	s = *j;
	while (tmp[*j] && ((tmp[*j] < 9 || tmp[*j] > 13) && tmp[*j] != ' '))
		(*j)++;
	t = *j;
	while (tmp[t] && ((tmp[t] >= 9 && tmp[t] <= 13) || tmp[t] == ' '))
		t++;
	if (tmp[t])
		fill_alias_multiple(ft_strsub(tmp, s, (*j) - s), alias, i);
	else
		fill_alias_multiple(ft_strsub(tmp, s, t - s), alias, i);
}
