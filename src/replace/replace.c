/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 17:27:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/30 18:00:13 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"
#include "../../includes/alias.h"

char		*make_string(char **array)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (array[i])
	{
		ft_strjoin_free(&res, array[i]);
		if (array[i + 1])
			ft_strjoin_free(&res, " ");
		i++;
	}
	return (res);
}

int			check_alias(char *array, t_var *var, t_replace *replace)
{
	int			i;
	t_replace	*r;
	t_var		*tmp_var;

	tmp_var = var;
	i = 0;
	r = replace;
	while (tmp_var && ((ft_strcmp(array, tmp_var->name) != 0)
	|| tmp_var->type != ALIAS))
		tmp_var = tmp_var->next;
	if (!tmp_var)
		return (0);
	// while (r)
	// {
	// 	if (ft_strcmp(r->name, tmp_var->name) == 0)
	// 		return (0);
	// 	r = r->next;
	// }
	return (1);
}

int			check_backslash_var(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 0 || str[i - 1] != '\\')
		return (1);
	return (0);
}

int			remove_env_while(t_alias *alias, t_var *var, t_replace *replace)
{
	int		done;
	int		i;

	done = 0;
	i = 0;
	if (check_alias(alias->data, var, replace) == 1 && alias->data[0] != '\\')
		replace_alias(alias, var, replace);
	while (alias)
	{
		if (alias->data && alias->data[0] != '\'')
		{
			if (alias->data && ft_strstr(alias->data, "$") != NULL &&
			check_backslash_var(alias->data))
			{
				done = 1;
				replace_var(var, alias);
				break ;
			}
		}
		alias = alias->next;
	}
	return (done);
}

// static void		print_list(t_alias *alias)
// {
// 	while (alias)
// 	{
// 		alias = alias->next;
// 	}
// }

char		**remove_env(t_var *start, char *str)
{
	char		**array;
	t_replace	*replace;
	t_alias		*alias;

	init_replace(&replace);
	array = split_space(str);
	alias = make_ar_to_list(array);
	//print_list(alias);
	replace->name = ft_strdup(alias->data);
	while (1)
	{
		if (remove_env_while(alias, start, replace) == 0)
			break ;
	}
	array = make_list_to_ar(alias);
	del_back_slash(&array);
	remoove_quote(&array);
	del_back_slash_end(&array);
	ft_strdel(&str);
	return (array);
}
