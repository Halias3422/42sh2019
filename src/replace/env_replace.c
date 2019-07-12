/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_replace.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:41:43 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 07:12:23 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"
#include "../../includes/alias.h"

int			cnt_list_var(t_tvar *var)
{
	int		nb;

	nb = 0;
	while (var)
	{
		var = var->next;
		nb++;
	}
	return (nb);
}

char		**make_list_to_ar_var(t_tvar *alias)
{
	char	**res;
	t_tvar	*s;
	int		i;

	s = alias;
	res = malloc(sizeof(char *) * (cnt_list_var(alias) + 1));
	i = 0;
	while (alias)
	{
		res[i] = ft_strdup(alias->data);
		i++;
		alias = alias->next;
	}
	res[i] = NULL;
	free_list_tvar(s);
	return (res);
}

t_tvar		*make_ar_to_list_var(char **str)
{
	t_tvar		*start;
	t_tvar		*var;
	int			i;

	var = malloc(sizeof(t_tvar));
	start = var;
	i = 0;
	while (str[i])
	{
		if (!var)
			var = malloc(sizeof(t_tvar));
		var->data = ft_strdup(str[i]);
		if (str[i + 1])
		{
			var->next = malloc(sizeof(t_var));
			var = var->next;
		}
		i++;
	}
	var->next = NULL;
	var = start;
	free_ar(str);
	return (var);
}

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
	{
		if (str[i] == '{')
		{
			i++;
			while (str[i] != '}')
				i++;
			break ;
		}
		else
			i++;
	}
	name = ft_strsub(str, s, i - s);
	tmp = get_the_data(name, env);
	if (str[s] && str[s - 1] && str[s - 1] == '{')
		res = ft_strjoin(ft_strsub(str, 0, s - 2), tmp);
	else
		res = ft_strjoin(ft_strsub(str, 0, s - 1), tmp);
	if (str[s] && str[s - 1] && str[s - 1] == '{')
		i++;
	s = i;
	while (str[i])
		i++;
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
