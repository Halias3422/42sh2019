/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/04 20:10:49 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/09 20:00:53 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"

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
	while (r)
	{
		if (ft_strcmp(r->name, tmp_var->name) == 0)
			return (0);
		r = r->next;
	}
	return (1);
}

int			remove_env_while(char ***array, t_var *var, t_replace *replace)
{
	int		done;
	int		i;

	done = 0;
	i = 0;
	if (check_alias((*array)[0], var, replace) == 1)
	{
		done = 1;
		(*array) = replace_alias(array, var, replace);
	}
	while ((*array)[i])
	{
		if ((*array)[i][0] != '\'')
		{
			if ((*array)[i] && ft_strstr((*array)[i], "$") != NULL)
			{
				done = 1;
				(*array) = replace_var(var, (*array));
				break ;
			}
		}
		i++;
	}
	return (done);
}

// TODO faire en sorte qu'on ne peut pas faire de boucle infinie comme bash on ne peut pas replace 2 fois une var. et tester les boucles

char		**remove_env(t_var *start, char *str)
{
	char		**array;
	t_replace	*replace;
	int			i = 0;

	init_replace(&replace);
	array = split_space(str);
	while (array[i])
	{
//		printf("%d: %s\n", i, array[i]);
		i++;
	}
	while (1)
	{
		if (remove_env_while(&array, start, replace) == 0)
			break ;
	}
	remoove_quote(&array);
	ft_strdel(&str);
	return (array);
}
