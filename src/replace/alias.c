/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/06 19:57:04 by mdelarbr    ###    #+. /#+    ###.fr     */
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

int			cnt_array(char ***str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		printf("str[%d]: _%s_\n", i, (*str)[i]);
		i++;
	}
	printf("le i du malloc: %d\n", i);
	return (i);
}

void		fill_array(char ***res, char ***array)
{
	int		i;

	i = 0;
	while ((*array)[i])
	{
		(*res)[i] = ft_strdup((*array)[i]);
		(i)++;
	}
	(*res)[i] = NULL;
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

int			end(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i + 1);
}

char		**fill_alias_solo(int *i, char *str, char ***array)
{
	char	**res;

	puts("solo");
	printf("str: _%s_\n", str);
	res = malloc(sizeof(char *) * (cnt_array(array) + 2));
	fill_array(&res, array);
	ft_strdel(&res[*i]);
	res[*i] = ft_strdup(str);
	res[end(*array)] = NULL;
	ft_strdel(&str);
	free_array(array);
	return (res);
}

char		**fill_alias_multiple(int *i, char *str, char ***array)
{
	char	**res;

	puts("multiple");
	printf("str: _%s_\n", str);
	res = malloc(sizeof(char *) * (cnt_array(array) + 2));
	fill_array(&res, array);
	ft_strdel(&res[*i]);
	res[*i] = ft_strdup(str);
	res[end(*array)] = NULL;
	ft_strdel(&str);
	free_array(array);
	(*i)++;
	return (res);
}

void		replace_alias_while(int *ind, t_var *var, char ***array)
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
			(*array) = fill_alias_solo(ind, ft_strsub(tmp, s, t - s), array);
			ft_strdel(&tmp);
			return ;
		}
		(*array) = fill_alias_multiple(ind, ft_strsub(tmp, s, j - s), array);
		j++;
		jump_space(tmp, &j);
	}
	ft_strdel(&tmp);
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

// faire attention quand le replace est plus long que array c'est un pb .oupss.

void		replace_alias(char ***array, t_var *var, t_replace *replace)
{
	int			i;
	t_replace	*tmp_r;
	t_var		*tmp_v;

	tmp_r = replace;
	tmp_v = var;
	i = 0;
	while (1)
	{
		while (var && (ft_strcmp((*array)[i], var->name) != 0 ||
		var->type != ALIAS))
			var = var->next;
		if (!var)
			return ;
		replace_alias_while(&i, var, array);
		if ((*array)[i + 1] && check_last_char((*array)[i]) == ' ')
			i++;
		else
		{
			printf("else\t\tarray: _%s_\n", (*array)[i + 1]);
			(*array)[i] = del_space((*array)[i]);
			break ;
		}
		var = tmp_v;
		printf("end\t\tarray - 1: _%s_\tarray: _%s_\n", (*array)[i - 1], (*array)[i]);
		(*array)[i - 1] = del_space((*array)[i - 1]);
	}
}
