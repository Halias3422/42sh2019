/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 14:26:57 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

int		replace_alias_first_part(t_var **s_var, t_alias *alias, t_replace *r)
{
	while ((*s_var) && (ft_strcmp(alias->data, (*s_var)->name) != 0 ||
	(*s_var)->type != ALIAS))
		(*s_var) = (*s_var)->next;
	if (!(*s_var))
		return (0);
	while (r->next)
		r = r->next;
	r->next = malloc(sizeof(t_replace));
	r = r->next;
	r->name = ft_strdup(alias->data);
	r->next = NULL;
	return (1);
}

int		replace_alias_last_part(t_alias *a, int *ret, t_var *var, t_replace *r)
{
	if (a->next && check_last_char(a, (*ret)) == ' ')
	{
		while ((*ret) - 1)
		{
			a = a->next;
			(*ret)--;
		}
	}
	else if (replace_alias_first_part(&var, a, r) == 1)
		return (1);
	else
	{
		a->data = del_space(a->data);
		return (0);
	}
	return (1);
}

int		check_tok(t_alias *alias, t_var *var, t_replace *replace)
{
	t_alias *tmp;

	tmp = alias;
	while (tmp)
	{
		if (tmp && tmp->next && (ft_strcmp(tmp->data, "&&") == 0
		|| ft_strcmp(tmp->data, "||") == 0 || ft_strcmp(tmp->data, ";") == 0
		|| ft_strcmp(tmp->data, "|") == 0))
		{
			replace_alias(tmp->next, var, replace);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		check_boucle(t_alias *alias, t_replace *replace)
{
	while (replace)
	{
		if (ft_strcmp(alias->data, replace->name) == 0)
			return (0);
		replace = replace->next;
	}
	return (1);
}

void	replace_alias(t_alias *alias, t_var *var, t_replace *replace)
{
	t_var		*s_var;
	int			ret;

	while (1)
	{
		s_var = var;
		if (replace_alias_first_part(&s_var, alias, replace) == 0)
			break ;
		ret = replace_alias_while(s_var, alias);
		if (check_boucle(alias, replace) == 0)
			break ;
		if (replace_alias_last_part(alias, &ret, var, replace) == 0)
			break ;
		alias->data = del_space(alias->data);
		if (alias->next)
			alias = alias->next;
	}
	check_tok(alias, var, replace);
	alias->data = del_space(alias->data);
}
