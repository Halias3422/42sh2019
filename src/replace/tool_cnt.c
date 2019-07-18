/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_cnt.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/15 05:45:24 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/17 00:59:48 by mdelarbr    ###    #+. /#+    ###.fr     */
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

int			cnt_size(char *str)
{
	int		nb;
	int		i;
	int		ret;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			i++;
		if (str[i] && (str[i] == '"' && (i == 0 || str[i - 1] != '\\')))
			cnt_size_double_quote(&i, &nb, str);
		if (str[i] && (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')))
			cnt_size_simple_quote(&i, &nb, str);
		else if (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
			if (cnt_printable_char(&nb, str, &i))
				break ;
		if (str[i] && (ret = find_token(str, i)) != -1)
		{
			nb++;
			i += g_fill_token[ret].size;
		}
	}
	return (nb);
}
