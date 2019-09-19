/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_bis.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 14:13:15 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 15:15:41 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lexeur.h"
#include "alias.h"

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
		if (basic_split_while(&i, str, res, &k) == 1)
			k++;
	}
	res[k] = 0;
	return (res);
}

int		basic_split_while(int *i, char *str, char **res, int *k)
{
	int		start;
	int		ret;

	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
	if (!(str[*i]))
		return (-1);
	start = *i;
	ret = find_token(str, *i);
	if (str[*i] && ((str[*i] >= '0' && str[*i] <= '9')
					|| (ret == 5 || ret == 8)))
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

int		replace_alias_while(t_var *var, t_alias *alias)
{
	char	*tmp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tmp = ft_strdup(var->data);
	if (!check_simple_or_multiple(tmp))
	{
		while (tmp[j])
			j++;
		fill_alias_solo(ft_strsub(tmp, 0, j), alias);
		return (1);
	}
	while (tmp[j])
	{
		replace_alias_while_fill(tmp, &j, &i, alias);
		jump_space(tmp, &j);
	}
	ft_strdel(&tmp);
	return (i);
}
