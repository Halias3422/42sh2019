/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_replace.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:41:43 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/15 04:37:03 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"
#include "../../includes/alias.h"

char		*get_the_data(char *name, t_var *env)
{
	t_var	*start;

	start = env;
	while (start && ft_strcmp(name, start->name) != 0)
		start = start->next;
	if (!start)
		return (ft_strdup(""));
	return (start->data);
}

int			find_second_char(char *str, int *i)
{
	if (str[*i] == '{')
	{
		(*i)++;
		while (str[*i] != '}')
			(*i)++;
		return (0);
	}
	else
		(*i)++;
	return (1);
}

char		*fill_res(char *str, int *i, char *tmp, int *s)
{
	char	*res;

	if (str[*s] && str[(*s) - 1] && str[(*s) - 1] == '{')
		res = ft_strjoin(ft_strsub(str, 0, (*s) - 2), tmp);
	else
		res = ft_strjoin(ft_strsub(str, 0, (*s) - 1), tmp);
	if (str[*s] && str[(*s) - 1] && str[(*s) - 1] == '{')
		(*i)++;
	*s = *i;
	while (str[*i])
		(*i)++;
	return (res);
}

char		*replace_var_to_data(char *str, t_var *env)
{
	char	*res;
	char	*name;
	char	*tmp;
	int		i;
	int		s;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	s = i;
	if (str[i] == '{')
		s = i + 1;
	while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '
	&& str[i] != '"' && str[i] != '\''))
		if (find_second_char(str, &i) == 0)
			break ;
	name = ft_strsub(str, s, i - s);
	tmp = get_the_data(name, env);
	res = fill_res(str, &i, tmp, &s);
	ft_strjoin_free(&res, ft_strsub(str, s, i - s));
	return (res);
}

char		**replace_var(t_var *env, char **str)
{
	t_tvar	*var;
	t_tvar	*start;
	char	**res;

	var = make_ar_to_list_var(str);
	start = var;
	while (var)
	{
		if (ft_strchr(var->data, '$'))
			var->data = replace_var_to_data(var->data, env);
		var = var->next;
	}
	var = start;
	res = make_list_to_ar_var(var);
	return (res);
}
