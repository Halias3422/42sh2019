/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_cnt.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:06:16 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 16:38:27 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		cnt_size_simple_quote(int *i, int *nb, char *str)
{
	(*i)++;
	(*nb)++;
	while (str[*i] && (str[*i] != '\'' && (*i == 0 || str[(*i) - 1] != '\\')))
		(*i)++;
	if (str[*i])
		(*i)++;
}

void		cnt_size_double_quote(int *i, int *nb, char *str)
{
	(*i)++;
	(*nb)++;
	while (str[*i] && (str[*i] != '"' && (*i == 0 || str[(*i) - 1] != '\\')))
		(*i)++;
	if (str[*i])
		(*i)++;
}

int			cnt_printable_char(int *nb, char *str, int *i)
{
	(*nb)++;
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& find_token(str, *i) == -1))
	{
		if (str[*i] == '"' && (*i == 0 || str[(*i) - 1] != '\\'))
			return (1);
		if (str[*i] == '\'' && (*i == 0 || str[(*i) - 1] != '\\'))
			return (1);
		(*i)++;
	}
	return (0);
}
