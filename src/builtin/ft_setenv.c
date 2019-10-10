/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 14:08:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 16:58:14 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		add_setenv(t_var **var, char *name, char *data, int usage)
{
	t_var	*start;

	if (usage == 0)
	{
		start = malloc(sizeof(t_var));
		start->name = name;
		start->data = data;
		start->type = ENVIRONEMENT;
		start->next = (*var);
		(*var) = start;
	}
	else if (usage == 1)
	{
		(*var) = malloc(sizeof(t_var));
		(*var)->next = NULL;
		(*var)->name = name;
		(*var)->data = data;
		(*var)->type = ENVIRONEMENT;
	}
}

static int	setenv_rules(t_process *p)
{
	if (p->cmd[1] && p->cmd[2])
	{
		ft_printf("42sh: setenv: too much arguments, use -u for usage\n");
		return (0);
	}
	if (p->cmd[1] && ft_strcmp(p->cmd[1], "-u") == 0)
	{
		ft_printf("42sh: setenv: usage: setenv [NAME=data, NAME, =NAME]\n");
		return (0);
	}
	return (1);
}

void		add_var_to_env(t_var **var, char *name, char *data)
{
	t_var	*prev;

	prev = NULL;
	if (!(*var))
	{
		add_setenv(var, name, data, 0);
		stock(*var, 5);
		return ;
	}
	while (*var)
	{
		if (ft_strcmp(name, (*var)->name) == 0)
			break ;
		prev = (*var);
		(*var) = (*var)->next;
	}
	if (!(*var))
	{
		add_setenv(var, name, data, 1);
		prev->next = (*var);
		return ;
	}
	ft_strdel(&(*var)->data);
	ft_strdel(&name);
	(*var)->data = data;
}

int			ft_setenv(t_process *p, t_var **var)
{
	char		**al;

	al = NULL;
	if (p->cmd[1])
	{
		al = malloc(sizeof(char *) * 3);
		al[0] = init_name(p->cmd[1]);
		al[1] = init_data(p->cmd[1]);
		al[2] = 0;
		remoove_quote(&al);
		if (check_name(al[0]) == 1)
			return (print_err_setenv(al));
		if (setenv_rules(p) == 0)
			return (0);
		if (scan_name_for_undesired_symbols(al[0]) == -1)
		{
			ft_free_tab(al);
			ft_printf_err("42sh: setenv: invalid name parameter\n");
			return (1);
		}
		add_var_to_env(var, al[0], al[1]);
	}
	free(al);
	return (0);
}
