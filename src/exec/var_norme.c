/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_norme.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:11:03 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:28:32 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		add_env_temp(t_var **var, char *str, int type)
{
	t_var	*start;
	char	*name;

	name = init_name(str);
	if (check_name(name) == 1)
	{
		ft_strdel(&name);
		return ;
	}
	start = malloc(sizeof(t_var));
	start->name = name;
	start->data = init_data(str);
	start->type = type;
	start->next = (*var);
	(*var) = start;
}

char		**remove_tab(char **src, int j)
{
	char	**res;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = 0;
	while (src[len])
		len++;
	if (len == 1)
		return (NULL);
	res = malloc(sizeof(char*) * len);
	i = -1;
	while (src[++i])
	{
		if (i == j)
			i++;
		if (i > len)
			break ;
		res[k] = ft_strdup(src[i]);
		k++;
	}
	res[len - 1] = NULL;
	return (res);
}

t_var		*add_one(char *str, char *name)
{
	t_var *var;

	var = malloc(sizeof(t_var));
	var->next = NULL;
	var->name = name;
	var->data = init_data(str);
	var->type = LOCAL;
	return (var);
}

int			add_env_check(char *name, t_var **var, char *str)
{
	if (check_name(name) == 1)
	{
		ft_strdel(&name);
		return (1);
	}
	if (!(*var))
	{
		add_env_temp(var, str, LOCAL);
		stock(*var, 5);
		return (1);
	}
	return (0);
}
