/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_reduction.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 10:28:45 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 10:31:11 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int		print_alias(t_var *var)
{
	while (var)
	{
		if (var->type == ALIAS)
			ft_printf("%s=%s\n", var->name, var->data);
		var = var->next;
	}
	return (0);
}

int		check_name(char *name)
{
	if ((ft_strcmp(name, "_") == 0) || (ft_strcmp(name, "?") == 0) ||
	(ft_strcmp(name, "!") == 0) || (ft_strcmp(name, "$") == 0) ||
	(ft_strcmp(name, "0") == 0))
		return (1);
	return (0);
}

int		print_err(char *name, char *data)
{
	ft_printf_err("42sh: alias:{B.T.red.} error{eoc}: Permission denied\n");
	ft_strdel(&name);
	ft_strdel(&data);
	return (1);
}

void	ft_free_deux(char *s, char *s1)
{
	ft_strdel(&s);
	ft_strdel(&s1);
}

int		error_unlias(char *str)
{
	ft_putstr("21sh: ");
	ft_putstr("unalias: ");
	ft_putstr(str);
	ft_putstr(": not found\n");
	return (1);
}
