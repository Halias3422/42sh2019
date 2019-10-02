/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 13:03:32 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

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
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (find_token(str, *i) == -1)))
		(*i)++;
}

int		basic_split_while(int *i, char *str, char **res, int *k)
{
	int		start;
	int		ret;

	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
	if (!str[*i])
		return (-1);
	start = *i;
	ret = find_token(str, *i);
	if (str[*i] && ((str[*i] >= '0' && str[*i] <= '9') ||
	(ret == 5 || ret == 8)))
		split_space_find_number(str, i);
	else if (search_agregator(str, *i))
		split_agregator(str, i);
	else
		split_space_basic(str, i);
	res[*k] = ft_strsub(str, start, (*i) - start);
	if (str[*i] && (ret = find_token(str, *i)) != -1)
	{
		(*k)++;
		res[*k] = ft_strsub(str, *i, g_fill_token[ret].size);
		(*i) += g_fill_token[ret].size;
	}
	return (1);
}

char	**split_space(char *str)
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

void	list_add(t_replace **replace, char *array)
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
