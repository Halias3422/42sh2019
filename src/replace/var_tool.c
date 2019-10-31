/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_tool.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:07:49 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 11:35:56 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
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
	res = ft_malloc(sizeof(char *) * (cnt_list_var(alias) + 1));
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

	var = ft_malloc(sizeof(t_tvar));
	start = var;
	i = 0;
	while (str[i])
	{
		if (!var)
			var = ft_malloc(sizeof(t_tvar));
		var->data = ft_strdup(str[i]);
		if (str[i + 1])
		{
			var->next = ft_malloc(sizeof(t_var));
			var = var->next;
		}
		i++;
	}
	var->next = NULL;
	var = start;
	free_ar(str);
	return (var);
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
