/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/12 15:20:56 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

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

void		print_list(t_alias *alias)
{
	while (alias)
	{
		printf("alias: _%s_\n", alias->data);
		alias = alias->next;
	}
}

void		fill_alias_solo(char *str, t_alias *alias)
{
	puts("solo");
	printf("str: _%s_\n", str);
	ft_strdel(&alias->data);
	alias->data = ft_strdup(str);
	print_list(alias);
//	fill_list(str, alias);
	ft_strdel(&str);
//	(*i)++;
}

void		fill_alias_multiple(char *str, t_alias *alias)
{
	puts("multiple");
	printf("str: _%s_\n", str);
	ft_strdel(&alias->data);
	alias->data = ft_strdup(str);
//	fill_list(str, alias);
	ft_strdel(&str);
	print_list(alias);
//	(*i)++;
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
			alias->prev = prev;
		alias->data = ft_strdup(str[i]);
		alias->next = NULL;
		prev = alias;
		alias = alias->next;
		i++;
	}
	return (start);
}

void		replace_alias_while(t_var *var, t_alias *alias)
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
			fill_alias_solo(ft_strsub(tmp, s, t - s), alias);
			break ;
		}
		fill_alias_multiple(ft_strsub(tmp, s, j - s), alias);
		j++;
		jump_space(tmp, &j);
	}
	ft_strdel(&tmp);
}

char		**replace_alias(char ***array, t_var *var, t_replace *replace)
{
//	char		**res;
	t_alias		*alias;

	alias = make_ar_to_list(*array);
	(void)replace;
	while (1)
	{
		while (var && (ft_strcmp(alias->data, var->name) != 0 ||
		var->type != ALIAS))
			var = var->next;
		if (!var)
			break ;
		replace_alias_while(var, alias);
		if (alias->next && check_last_char(alias->data) == ' ')
			alias = alias->next;
		else
		{
			alias->data = del_space(alias->data);
			break ;
		}
		alias->prev->data = del_space(alias->prev->data);
	}
	return (*array);
}
