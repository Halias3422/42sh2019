/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 11:14:54 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

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
		if (str[*i] && (ret == 4 || ret == 6 || ret == 9))
		{
			(*i) += g_fill_token[ret].size;
			return ;
		}
		if (ret == 5 || ret == 8)
		{
			(*i) += g_fill_token[ret].size;
			if (str[*i + 1])
				(*i)++;
			while (str[*i] && (str[*i] < 9 || str[*i] > 13) && str[*i] != ' ')
				(*i)++;
		}
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

int		search_agregator(char *str, int i)
{
	int		token;

	while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
	{
		token = find_token(str, i);
		if (token == 5 || token == 8)
			return (1);
		i++;
	}
	return (0);
}

void	split_agregator(char *str, int *i)
{
	while (str[*i] && (find_token(str, *i) != 5 && find_token(str, *i) != 8))
		(*i)++;
	(*i) += 2;
	if (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
	{
		while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
			(*i)++;
	}
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '))
		(*i)++;
}

int		basic_split_while(int *i, char *str, char **res, int *k)
{
	int		start;
	int		ret;

	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
	if (str[*i])
	{
		start = *i;
		ret = find_token(str, *i);
		if (str[*i] && ((str[*i] >= '0' && str[*i] <= '9') || (ret == 5 || ret == 8)))
			split_space_find_number(str, i);
		else if (search_agregator(str, *i))
			split_agregator(str, i);
		else
			split_space_basic(str, i);
		res[*k] = ft_strsub(str, start, (*i) - start);
	}
	else
		return (-1);
	if (str[*i] && (ret = find_token(str, *i)) != -1)
	{
		(*k)++;
		res[*k] = ft_strsub(str, *i, g_fill_token[ret].size);
		(*i) += g_fill_token[ret].size;
	}
	return (1);
}

char		**split_space(char *str)
{
	int		i;
	int		k;
	char	**res;

	i = 0;
	k = 0;
	res = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (basic_split_while(&i, str, res, &k) == 1)
			k++;
	}
	res[k] = 0;
	return (res);
}

void		list_add(t_replace **replace, char *array)
{
	t_replace	*next;
	t_replace	*start;

	start = (*replace);
	while ((*replace)->next)
		(*replace) = (*replace)->next;
	next = malloc(sizeof(t_replace));
	next->name = ft_strdup(array);
	next->next = NULL;
	(*replace)->next = next;
	(*replace) = start;
}
