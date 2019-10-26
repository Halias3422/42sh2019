/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_replace.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:44:11 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/26 11:09:13 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"
#include "../../includes/alias.h"

char			*get_the_data(char *name, t_var *env)
{
	t_var	*start;

	start = env;
	while (start && ft_strcmp(name, start->name) != 0)
		start = start->next;
	if (!start)
		return (ft_strdup(""));
	return (ft_strdup(start->data));
}

char			*fill_res(char *str, int *i, char *tmp, int *s)
{
	char	*res;

	if (str[*s] && str[(*s) - 1] && str[(*s) - 1] == '{')
		res = ft_strjoinf(ft_strsub(str, 0, (*s) - 2), tmp, 3);
	else
		res = ft_strjoinf(ft_strsub(str, 0, (*s) - 1), tmp, 3);
	if (str[*s] && str[(*s) - 1] && str[(*s) - 1] == '{')
		(*i)++;
	*s = *i;
	while (str[*i])
		(*i)++;
	return (res);
}

int				alpha_numeric_condition(char *str, int i)
{
	if (str[i] && ((str[i] >= 'a' && str[i] <= 'z') ||
	(str[i] >= 'A' && str[i] <= 'Z') ||
	(str[i] >= '0' && str[i] <= '9') || str[i] == '0' || str[i] == '$' ||
	str[i] == '?' || str[i] == '!' || str[i] == '_'))
		return (1);
	return (0);
}

char			*replace_var_to_data(char *str, t_var *env)
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
		s = i++ + 1;
	while (alpha_numeric_condition(str, i))
		if (find_second_char(str, &i) == 0)
			break ;
	name = ft_strsub(str, s, i - s);
	tmp = get_the_data(name, env);
	ft_strdel(&name);
	res = fill_res(str, &i, tmp, &s);
	res = ft_strjoinf(res, ft_strsub(str, s, i - s), 3);
	ft_strdel(&str);
	return (res);
}

void			replace_var(t_var *env, t_alias *alias)
{
	while (alias)
	{
		if (ft_strchr(alias->data, '$'))
			alias->data = replace_var_to_data(alias->data, env);
		alias = alias->next;
	}
}
