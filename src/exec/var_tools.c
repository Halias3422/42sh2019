/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_tools.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 14:57:40 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/21 17:08:47 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"
#include "lexeur.h"

void		free_temp(t_var **var)
{
	t_var *tmp;
	t_var *next;

	tmp = (*var);
	while (*var)
	{
		if ((*var)->type == TEMP)
		{
			ft_strdel(&(*var)->name);
			ft_strdel(&(*var)->data);
			next = (*var)->next;
			free(*var);
			(*var) = next;
			if (!tmp)
				tmp = (*var);
		}
		if ((*var)->type != TEMP)
			break ;
		(*var) = (*var)->next;
	}
}

int			find_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int			check_cmd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (find_equal(str[i]) == 1)
		{
			if (str[i + 1])
				return (1);
		}
		i++;
	}
	return (0);
}
