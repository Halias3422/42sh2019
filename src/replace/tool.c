/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/30 18:39:27 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		split_space_find_number(char *str, int *i)
{
	int		ret;

	ret = 0;
	if (((ret) = find_token(str, *i)) != -1)
	{
		(*i) += g_fill_token[ret].size;
		while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
			(*i)++;
	}
	else
	{
		while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
			(*i)++;
		if (str[*i])
			ret = find_token(str, *i);
		if (str[*i] && ((ret) >= 4 && (ret) <= 7))
			*i += g_fill_token[ret].size;
	}
}

void		split_space_basic(char *str, int *i)
{
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (find_token(str, *i) == -1)))
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

void		basic_split_while(int *i, char *str, char **res, int *k)
{
	int		start;
	int		ret;

	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
	if (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' ' && find_token(str, *i) == -1))
	{
		start = *i;
		if (str[*i] && ((str[*i] >= '0' && str[*i] <= '9') &&
		(find_token(str, *i) == 9 && find_token(str, *i) == 10)))
		{
			//modifier la condition pour les >& et <& 
			//TODO gerer les int collé avant les redirections les zapper
			puts("oups");
			split_space_find_number(str, i);
		}
		else
		{
			puts("okk");
			split_space_basic(str, i);
		}
		res[*k] = ft_strsub(str, start, (*i) - start);
		printf("\t=->>\tres[%d]: _%s_\n", *k, res[*k]);
		(*k)++;
	}
	if (str[*i] && (ret = find_token(str, *i)) != -1)
	{
		res[*k] = ft_strsub(str, *i, g_fill_token[ret].size);
		printf("\t=->>\tres[%d]: _%s_\n", *k, res[*k]);
		(*i) += g_fill_token[ret].size - 1;
		(*k)++;
	}
	printf("str[%d]: _%c_\n", *i, str[*i]);
	if (str[*i])
		(*i)++;
}

char		**split_space(char *str)
{
	int		i;
	int		k;
	char	**res;

	i = 0;
	k = 0;
	res = malloc(sizeof(char *) * (cnt_size(str) + 1));
	while (str[i])
	{
		basic_split_while(&i, str, res, &k);
	}
	res[k] = NULL;
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
