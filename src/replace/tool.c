/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/05 11:43:04 by mdelarbr    ###    #+. /#+    ###.fr     */
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
		printf("number :: ret -> %d\tname_%s_\n", ret, g_fill_token[ret].name);
		if (str[*i] && (ret == 4 || ret == 6 || ret == 9))
			return ;
			//*i += (g_fill_token[ret].size - 1);
		if (ret == 5 || ret == 8)
		{
	//		puts(">& or <&");
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

void		split_space_basic(char *str, int *i)
{
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (find_token(str, *i) == -1) && (check_token_after_number(str, *i))))//mettre la fonction ici
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
	if (str[*i])
	{
		start = *i;
		ret = find_token(str, *i);
//		printf("ret -> %d\tname -> _%s_\n", ret, g_fill_token[ret].name);
		if (str[*i] && ((str[*i] >= '0' && str[*i] <= '9') || (ret == 5 || ret == 8)))
				split_space_find_number(str, i);
		else
			split_space_basic(str, i);
		res[*k] = ft_strsub(str, start, (*i) - start);
	}
	if (str[*i] && (ret = find_token(str, *i)) != -1)
	{
		ft_strjoin_free(&res[*k], ft_strsub(str, *i, g_fill_token[ret].size));
		(*i) += g_fill_token[ret].size - 1;
	}
	printf("__res[%d] -> |%s|__\n", *k, res[*k]);
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
		k++;
		if (str[i])
			i++;
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
