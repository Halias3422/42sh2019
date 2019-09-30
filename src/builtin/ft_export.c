/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_export.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 15:23:43 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:01:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int			ft_export_env(char *name, t_var **ptr_var)
{
	t_var *var;

	var = *ptr_var;
	if (ft_get_val(name, var, LOCAL) == NULL)
		return (0);
	while (var)
	{
		if (ft_strcmp(name, var->name) == 0 && var->type == LOCAL)
		{
			var->type = ENVIRONEMENT;
			return (1);
		}
		var = var->next;
	}
	return (0);
}

void		print_p(t_var **ptr_var)
{
	t_var	*var;

	var = *ptr_var;
	while (var != NULL)
	{
		if (var->type == ENVIRONEMENT)
		{
			if (var->name && var->data)
				ft_printf("export %s=%s\n", var->name, var->data);
			else if (var->name)
				ft_printf("export %s\n", var->name);
		}
		var = var->next;
	}
}

int			ft_export(t_process *p, t_var **ptr_var)
{
	int i;

	i = 0;
	if (ft_tabclen(p->cmd) > 1 && ft_strcmp(p->cmd[1], "-p") == 0)
	{
		print_p(ptr_var);
		return (0);
	}
	while (p->cmd[++i])
	{
		if (!ft_export_env(p->cmd[i], ptr_var))
			ft_printf("42sh: no matches found: %s", p->cmd[i]);
	}
	return (0);
}
