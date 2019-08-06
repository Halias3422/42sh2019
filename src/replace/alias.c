/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/06 11:09:37 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

void		replace_alias_while_fill(char *tmp, int *j, int *i, t_alias *alias)
{
	int		t;
	int		s;

	s = *j;
	while (tmp[*j] && ((tmp[*j] < 9 || tmp[*j] > 13) && tmp[*j] != ' '))
		(*j)++;
	t = *j;
	while (tmp[t] && ((tmp[t] >= 9 && tmp[t] <= 13) || tmp[t] == ' '))
		t++;
	if (tmp[t])
		fill_alias_multiple(ft_strsub(tmp, s, (*j) - s), alias, i);
	else
		fill_alias_multiple(ft_strsub(tmp, s, t - s), alias, i);
}

int			replace_alias_while(t_var *var, t_alias *alias)
{
	char	*tmp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tmp = ft_strdup(var->data);
	if (!check_simple_or_multiple(tmp))
	{
		while (tmp[j])
			j++;
		fill_alias_solo(ft_strsub(tmp, 0, j), alias);
		return (1);
	}
	while (tmp[j])
	{
		replace_alias_while_fill(tmp, &j, &i, alias);
		jump_space(tmp, &j);
	}
	ft_strdel(&tmp);
	return (i);
}

int			replace_alias_first_part(t_var **s_var, t_alias *alias)
{
	while ((*s_var) && (ft_strcmp(alias->data, (*s_var)->name) != 0 ||
	(*s_var)->type != ALIAS))
		(*s_var) = (*s_var)->next;
	if (!(*s_var))
		return (0);
	return (1);
}

int			replace_alias_last_part(t_alias *alias, int *ret)
{
	if (alias->next && check_last_char(alias, (*ret)) == ' ')
	{
		while ((*ret) - 1)
		{
			alias = alias->next;
			(*ret)--;
		}
	}
	else
	{
		alias->data = del_space(alias->data);
		return (0);
	}
	return (1);
}

// boucles infines sur alias ls='ls -G'. (il faut gerer les boucles infinies et on est bon)

static void		print_list(t_alias *alias)
{
	int i = 0;
	while (alias)
	{
		printf("alias->data = %s\n", alias->data);
		alias = alias->next;
		i++;
		if (i >= 10)
			__builtin_abort();		
	}
	puts("-------------------------------------------------------------------------------");
}

void		replace_alias(t_alias *alias, t_var *var, t_replace *replace)
{
	t_var		*s_var;
	int			ret;
	int			i = 0;

	(void)replace;
	puts("===============================================================================");
	printf("function : replace_alias\n");
	while (1)
	{
		s_var = var;
		printf("avant :alias->data = %s\n", alias->data);
		if (replace_alias_first_part(&s_var, alias) == 0)
		{
			printf("break 1 :alias->data = %s\n", alias->data);
			break ;
		}
		print_list(alias);
		ret = replace_alias_while(s_var, alias);
		print_list(alias);
		__builtin_abort();
		if (replace_alias_last_part(alias, &ret) == 0)
		{
			printf("break 2 :alias->data = %s\n", alias->data);
			break ;
		}
		alias->data = del_space(alias->data);
		printf("apres :alias->data = %s\n", alias->data);
		if (alias->next)
			alias = alias->next;
		i++;
		if (i >= 10)
			__builtin_abort();
	}
	alias->data = del_space(alias->data);
}

// char		**replace_alias(char ***array, t_var *var, t_replace *replace)
// {
// 	char		**res;
// 	t_alias		*alias;
// 	t_alias		*start;
// 	t_var		*s_var;
// 	int			ret;

// 	alias = make_ar_to_list(*array);
// 	start = alias;
// 	(void)replace;
// 	alias = start;
// 	while (1)
// 	{
// 		s_var = var;
// 		if (replace_alias_first_part(&s_var, alias) == 0)
// 			break ;
// 		ret = replace_alias_while(s_var, alias);
// 		if (replace_alias_last_part(alias, &ret) == 0)
// 			break ;
// 		alias->data = del_space(alias->data);
// 		if (alias->next)
// 			alias = alias->next;
// 	}
// 	alias->data = del_space(alias->data);
// 	res = make_list_to_ar(start);
// 	return (res);
// }

// static void		print_tab(char **array)
// {
// 	int i = 0;
// 	static int j = 0;

// 	while (array[i])
// 	{
// 		printf("array1[%d]=%s\t", i, array[i]);
// 		i++;
// 	}
// 	puts("");
// 	j++;
// 	if (j == 5)
// 	 	exit(1);
// }

// char		**replace_alias(char ***array, t_var *var, t_replace *replace)
// {
// 	// t_alias		*alias;
// 	// t_alias		*start;
// 	t_var		*s_var;
// 	int			i;

// 	// start = alias;
// 	(void)replace;
// 	// alias = start;
// 	i = 0;
// 	s_var = var;
// 	while ((*array)[i])
// 	{
// 		while (s_var)
// 		{
// 			if (ft_strcmp(s_var->name, (*array)[i]) == 0)
// 			{
// 				ft_strdel(array[i]);
// 				(*array)[i] = ft_strdup(s_var->data);
// 				break ;
// 			}
// 			s_var = s_var->next;
// 		}
// 		(*array)[i] = del_space((*array)[i]);
// 		i++;
// 	}
// 	print_tab(*array);
// //	alias->data = del_space(alias->data);
// 	return (*array);
// }
