/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 17:27:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/26 09:18:31 by mjalenqu    ###    #+. /#+    ###.fr     */
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
	return (1);
}

int			check_backslash_var(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 0 || str[i - 1] != '\\')
	{
		if (i == 0 && !str[i + 1])
			return (0);
		return (1);
	}
	if (!str[i + 1] || (str[i + 1] && str[i + 1] == ' '))
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
	check_tok(alias, var, replace);
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

void		free_alias(t_alias *alias)
{
	t_alias *tmp;

	tmp = alias;
	while (alias)
	{
		tmp = alias->next;
		ft_strdel(&alias->data);
		free(alias);
		alias = tmp;
	}
	alias = NULL;
}

char		**start_split(t_var *start, char *str)
{
	char		**ar;
	t_replace	*replace;
	t_alias		*alias;

	init_replace(&replace);
	ar = split_space(str);
	if (!start)
		return (ar);
	alias = make_ar_to_list(ar);
	replace->name = ft_strdup(alias->data);
	while (1)
	{
		if (remove_env_while(alias, start, replace) == 0)
			break ;
	}
	// ft_free_tab(ar);
	ar = make_list_to_ar(alias);
	free_replace(replace);
	free_alias(alias);
	del_back_slash(&ar);
	remoove_quote(&ar);
	del_back_slash_end(&ar);
	ft_strdel(&str);
	return (ar);
}
