/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/30 11:16:24 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char		check_last_char(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	printf("str[i - 1]: %c\n", str[i - 1]);
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

void		fill_array(char ***res, char ***array, int *i)
{
	while ((*array)[*i])
	{
		(*res)[*i] = ft_strdup((*array)[*i]);
		printf("res[%d]: _%s_\n", *i, (*res)[*i]);
		(*i)++;
	}
	(*res)[*i] = NULL;
}

char		**fill_alias_solo(char *str, char ***array)
{
	char 	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (cnt_array((*array)) + 1));
	res[i] = ft_strdup(str);
	printf("res[%d]: _%s_\n", i, res[i]);
	fill_array(&res, array, &i);
	ft_strdel(&str);
//	free_array(array);
	return (res);
}

void		fill_alias_multiple(int i, char *str, char ***array)
{
	i = 0;
	str = NULL;
	array = NULL;
//replace  i eme alias dans array.
}

void		replace_alias_while(t_var *var, char ***array)
{
	char	*tmp;
	int		j;
	int		i;
	int		t;
	int		s;
	int		test = 0;

	j = 0;
	i = 0;
	tmp = ft_strdup(var->data);
	while (tmp[j])
	{
		s = j;
		while (tmp[j] && ((tmp[j] < 9 || tmp[j] > 13) && tmp[j] != ' '))
			j++;
		t = j;
		while (tmp[t] && ((tmp[t] >= 9 && tmp[t] <= 13) || tmp[t] == ' '))
			t++;
		if (!tmp[t])
		{
			(*array) = fill_alias_solo(ft_strsub(tmp, s, t - s), array);
			while ((*array)[test])
			{
				printf("ar[%d]: _%s_\n", test, (*array)[test]);
				test++;
			}
			return ;
		}
		fill_alias_multiple(i, ft_strsub(tmp, s, i - s), array);
		j++;
	}
}

void		replace_alias(char ***array, t_var *var, t_replace *replace)
{
	int			i;
	t_replace	*tmp_r;

	tmp_r = replace;
	i = 0;
	while (1)
	{
		while (var && (ft_strcmp((*array)[i], var->name) != 0 &&
		var->type != ALIAS))
			var = var->next;
		if (!var)
			return ;
		replace_alias_while(var, array);
		if (check_last_char((*array)[i]) == ' ')
			i++;
		else
			break ;
	}
	list_add(&replace, (*array)[i]);
	ft_strdel(array[i]);
}
