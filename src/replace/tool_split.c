/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_split.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/23 16:46:19 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 14:07:49 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		token_8_and_5(int *i, int ret, char *str)
{
	(*i) += g_fill_token[ret].size;
	if (str[*i + 1])
		(*i)++;
	while (str[*i] && (str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (find_token(str, *i) == -1))
		(*i)++;
}

void		split_space_find_number(char *str, int *i)
{
	int		ret;

	ret = 0;
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
		(*i)++;
	if (str[*i])
	{
		ret = find_token(str, *i);
		if (ret == -1)
		{
			while (str[*i] && (str[*i] < 9 || str[*i] > 13) && str[*i] != ' ')
				(*i)++;
		}
		if (str[*i] && (ret == 4 || ret == 6 || ret == 9 || ret == 7))
		{
			(*i) += g_fill_token[ret].size;
			return ;
		}
		if (ret == 5 || ret == 8)
			token_8_and_5(i, ret, str);
	}
}

int			check_token_after_number(char *str, int i)
{
	int ret;

	if (str[i] && ((str[i] >= '0' && str[i] <= '9')))
	{
		while (str[i] && (str[i] >= '0' && str[i] <= '9'))
			i++;
		if (str[i])
		{
			ret = find_token(str, i);
			if (ret == 4 || ret == 5 || ret == 6 || ret == 8 || ret == 9)
				return (0);
		}
	}
	return (1);
}

int			double_check(char *str, int i)
{
	if (find_token(str, i) != -1)
	{
		if (i != 0 && str[i - 1] == '\\')
			return (1);
		return (0);
	}
	return (1);
}

void		split_space_basic(char *str, int *i)
{
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (double_check(str, *i))))
	{
		if (str[*i] == '\'' && (*i == 0 || str[(*i) - 1] != '\\'))
		{
			while (str[++(*i)])
				if (str[*i] == '\'' && (*i == 0 || str[(*i) - 1] != '\\'))
					break ;
		}
		if (str[*i] == '"' && (*i == 0 || str[(*i) - 1] != '\\'))
		{
			while (str[++(*i)])
				if (str[*i] == '"' && ((*i) == 0 || str[(*i) - 1] != '\\'))
					break ;
		}
		if (str[*i] == '\\' && str[*i + 1] == ' ')
			(*i)++;
		if (str[*i])
			(*i)++;
	}
}