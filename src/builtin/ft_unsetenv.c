/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsetenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 15:50:21 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 11:01:18 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

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

int			verif_empty_env(t_var **var)
{
	if (*var == NULL)
	{
		ft_printf("var est NULL maintenant\n");
	}
	if ((*var)->name == NULL)
	{
		ft_printf("var name est null\n");
	}
	ft_printf("sortie du verif\n");
	return (1);
}

int			ft_unsetenv(t_process *p, t_var **var)
{
	if (*var && p->cmd[1])
	{
		if (unsetenv_rules(p) == 0)
			return (0);
		if (remove_list_var(var, ENVIRONEMENT, p->cmd[1]) == 1)
		{
			stock(*var, 5);
			return (1);
		}
		else
		{
			ft_printf("42sh: unsetenv: var %s not found\n", p->cmd[1]);
			return (0);
		}
	}
	else if (*var == NULL)
		ft_printf("42sh: unsetenv: environment not set\n");
	else
		ft_printf("42sh: unsetenv: bad parameters, use -u for usage\n");
	return (0);
}
