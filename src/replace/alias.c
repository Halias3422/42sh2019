/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 11:58:02 by mdelarbr    ###    #+. /#+    ###.fr     */
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
		(*i)++;
	}
	(*res)[*i] = NULL;
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

char		**fill_alias_solo(char *str, char ***array)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (cnt_array((*array)) + 1));
	res[i] = ft_strdup(str);
	i++;
	fill_array(&res, array, &i);
	ft_strdel(&str);
	free_array(array);
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
			return ;
		}
		fill_alias_multiple(i, ft_strsub(tmp, s, i - s), array);
		j++;
	}
}

char		*del_space(char *str)
{
	int		i;
	int		s;
	char	*tmp;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		jump_space(str, &i);
		s = i;
		while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
			i++;
		tmp = ft_strsub(str, s, i - s);
		ft_strjoin_free(&res, tmp);
		ft_strdel(&tmp);
		if (str[i])
			i++;
	}
	ft_strdel(&str);
	return (res);
}

void		replace_alias(char ***array, t_var *var, t_replace *replace)
{
	int			i;
	t_replace	*tmp_r;

	tmp_r = replace;
	i = 0;
	while (1)
	{
		while (var && (ft_strcmp((*array)[i], var->name) != 0 || var->type != ALIAS))
			var = var->next;
		if (!var)
			return ;
		replace_alias_while(var, array);
		if ((*array)[i + 1] && check_last_char((*array)[i]) == ' ')
			i++;
		else
		{
			printf("b: avant: array: _%s_\n", (*array)[i]);
			(*array)[i] = del_space((*array)[i]);
			printf("b: apres array: _%s_\n", (*array)[i]);
			break ;
		}
		//enlever les espaces sur ce qui a etait replace merci.
		printf("avant: array: _%s_\n", (*array)[i - 1]);
		(*array)[i - 1] = del_space((*array)[i - 1]);
		printf("apres array: _%s_\n", (*array)[i - 1]);
	}
}
