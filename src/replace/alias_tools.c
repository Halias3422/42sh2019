/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/12 12:34:55 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/12 12:34:57 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

char		check_last_char(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (str[i - 1]);
}

int			cnt_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		fill_array(char ***res, char ***array)
{
	int		i;

	i = 0;
	while ((*array)[i])
	{
		(*res)[i] = ft_strdup((*array)[i]);
		(i)++;
	}
	(*res)[i] = NULL;
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
