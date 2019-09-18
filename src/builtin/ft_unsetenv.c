/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsetenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 15:50:21 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 14:22:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static int	element_already_exists_and_remove(char *element, t_var *var)
{
	t_var	*tmp;

	tmp = var;
	while (var != NULL)
	{
		while (var != NULL && ft_strcmp(element, var->name) != 0)
			var = var->next;
		if (var != NULL && var->type != ENVIRONEMENT)
			var = var->next;
		else
			break;
	}
	if (var == NULL)
		return (0);
	while (tmp && tmp->next && ft_strcmp(tmp->next->name, var->name) != 0)
		tmp = tmp->next;
	var = var->next;
	tmp->next = var;
	return (1);
}

static int	unsetenv_rules(t_process *p)
{
	if (p->cmd[1] && p->cmd[2])
	{
		ft_printf("42sh: unsetenv: too much arguments, use -u for usage\n");
		return (0);
	}
	if (p->cmd[1] && ft_strcmp(p->cmd[1], "-u") == 0)
	{
		ft_printf("42sh: unsetenv: usage: unsetenv [NAME]\n");
		return (0);
	}
	return (1);
}

int			ft_unsetenv(t_process *p, t_var **var)
{
	if (p->cmd[1])
	{
		if (unsetenv_rules(p) == 0)
			return (0);
		if (element_already_exists_and_remove(p->cmd[1], *var) == 1)
		{
			print_env(var);
			return (1);
		}
		else
		{
			ft_printf("42sh: unsetenv: var %s not found\n", p->cmd[1]);
			return (0);
		}
	}
	ft_printf("42sh: unsetenv: bad parameters, use -u for usage\n");
	return (0);
}
