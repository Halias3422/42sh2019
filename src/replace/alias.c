/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/14 11:36:39 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

int			cnt_list(t_alias *alias)
{
	int		nb;

	nb = 0;
	while (alias)
	{
		alias = alias->next;
		nb++;
	}
	return (nb);
}

char		**make_list_to_ar(t_alias *alias)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (cnt_list(alias) + 1));
	i = 0;
	while (alias)
	{
		res[i] = ft_strdup(alias->data);
		i++;
		alias = alias->next;
	}
	res[i] = NULL;
	return (res);
}

t_alias		*make_ar_to_list(char **str)
{
	t_alias		*start;
	t_alias		*alias;
	t_alias		*prev;
	int			i;

	alias = malloc(sizeof(t_alias));
	start = alias;
	i = 0;
	while (str[i])
	{
		if (!alias)
			alias = malloc(sizeof(t_alias));
		if (i == 0)
			alias->prev = NULL;
		else
		{
			alias->prev = prev;
		}
		alias->data = ft_strdup(str[i]);
		prev = alias;
		if (str[i + 1])
		{
			alias->next = malloc(sizeof(t_alias));
			alias = alias->next;
		}
		i++;
	}
	alias->next = NULL;
	alias = start;
	return (start);
}

int			check_simple_or_multiple(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
			i++;
		j = i;
		while (str[j] && ((str[j] >= 9 && str[j] <= 13) || str[j] == ' '))
			j++;
		if (!str[j])
			return (0);
		return (1);
	}
	return (1);
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

void		fill_alias_solo(char *str, t_alias *alias)
{
	ft_strdel(&alias->data);
	alias->data = ft_strdup(str);
	ft_strdel(&str);
}

void		ft_add_list(t_alias *alias, int i, char *str)
{
	int		j;
	t_alias	*new;

	new = malloc(sizeof(t_alias));
	new->data = ft_strdup(str);
	j = 0;
	while (j < i - 1)
	{
		alias = alias->next;
		j++;
	}
	new->next = alias->next;
	new->prev = alias;
	alias->next = new;
}

void		fill_alias_multiple(char *str, t_alias *alias, int *i)
{
	if (*i >= 1)
		ft_add_list(alias, *i, str);
	else
	{
		ft_strdel(&alias->data);
		alias->data = ft_strdup(str);
	}
	ft_strdel(&str);
	(*i)++;
}

int		replace_alias_while(t_var *var, t_alias *alias)
{
	char	*tmp;
	int		j;
	int		i;
	int		t;
	int		s;

	j = 0;
	i = 0;
	tmp = ft_strdup(var->data);
	if (!check_simple_or_multiple(tmp))
	{
		while (tmp[j] && ((tmp[j] < 9 || tmp[j] > 13) && tmp[j] != ' '))
			j++;
		fill_alias_solo(ft_strsub(tmp, 0, j), alias);
		return (0);
	}
	while (tmp[j])
	{
		s = j;
		while (tmp[j] && ((tmp[j] < 9 || tmp[j] > 13) && tmp[j] != ' '))
			j++;
		t = j;
		while (tmp[t] && ((tmp[t] >= 9 && tmp[t] <= 13) || tmp[t] == ' '))
			t++;
		if (tmp[t])
			fill_alias_multiple(ft_strsub(tmp, s, j - s), alias, &i);
		else
			fill_alias_multiple(ft_strsub(tmp, s, t - s), alias, &i);
		jump_space(tmp, &j);
	}
	ft_strdel(&tmp);
	return (i);
}

char		**replace_alias(char ***array, t_var *var, t_replace *replace)
{
	char		**res;
	t_alias		*alias;
	t_alias		*start;
	t_var		*s_var;
	int			ret;

	alias = make_ar_to_list(*array);
	start = alias;
	(void)replace;
	while (1)
	{
		s_var = var;
		while (s_var && (ft_strcmp(alias->data, s_var->name) != 0 ||
		s_var->type != ALIAS))
			s_var = s_var->next;
		if (!s_var)
			break ;
		ret = replace_alias_while(s_var, alias);
		if (alias->next && check_last_char(alias, ret) == ' ')
		{
			while (ret - 1)
			{
				alias = alias->next;
				ret--;
			}
		}
		else
		{
			alias->data = del_space(alias->data);
			break ;
		}
		alias->data = del_space(alias->data);
		alias = alias->next;
	}
	res = make_list_to_ar(start);
	return (res);
}
