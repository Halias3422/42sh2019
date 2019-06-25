/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 17:33:09 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char		**fill_alias_solo(int i, char *str, char ***array)
{
	char	**res;

	res = malloc(sizeof(char *) * (cnt_array((*array)) + 1));
	fill_array(&res, array);
	ft_strdel(&res[i]);
	res[i] = ft_strdup(str);
	ft_strdel(&str);
	free_array(array);
	return (res);
}

void		fill_alias_multiple(int i, char *str, char ***array)
{
	i = 0;
	str = NULL;
	array = NULL;
// TODO replace  i eme alias dans array.
}

void		replace_alias_while(int ind, t_var *var, char ***array)
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
			break ;
		}
		fill_alias_multiple(i, ft_strsub(tmp, s, i - s), array);
		j++;
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
		replace_alias_while(i, var, array);
		if ((*array)[i + 1] && check_last_char((*array)[i]) == ' ')
			i++;
		else
		{
			(*array)[i] = del_space((*array)[i]);
			break ;
		}
		var = tmp_v;
		(*array)[i - 1] = del_space((*array)[i - 1]);
	}
}
