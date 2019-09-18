/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 14:08:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 09:38:00 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		print_env(t_var **var)
{
	while (*var)
	{
		if ((*var)->type == ENVIRONEMENT)
		{
			ft_printf("%s=", (*var)->name);
			ft_printf("%s\n", (*var)->data);
		}
		(*var) = (*var)->next;
	}
}

static int	element_already_exists_and_replace(char **element, t_var *var)
{
	while (var != NULL && ft_strcmp(element[0], var->name) != 0)
		var = var->next;
	if (var == NULL)
		return (0);
	free(var->data);
	free(var->name);
	var->name = element[0];
	var->data = element[1];
	return (1);
}

static void	add_var_to_env(t_var *var, char **element)
{
	t_var		*new;

	while (var->next != NULL)
		var = var->next;
	new = (t_var*)malloc(sizeof(t_var));
	new->name = element[0];
	new->data = element[1];
	new->type = ENVIRONEMENT;
	new->next = NULL;
	var->next = new;
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

int			ft_setenv(t_process *p, t_var **var)
{
	char		**new_element;

	if (p->cmd[1])
	{
		if (setenv_rules(p) == 0)
			return (0);
		new_element = ft_strsplit(p->cmd[1], '=');
		if ((new_element[1] && new_element[2]) || (new_element[0] == NULL &&
					new_element[1] == NULL) || p->cmd[1][0] == '=')
		{
			ft_tabfree(new_element);
			ft_printf("42sh: setenv: bad parameters, use -u for usage\n");
			return (0);
		}
		if (element_already_exists_and_replace(new_element, *var) == 1)
		{
			free(new_element);
			print_env(var);
			return (1);
		}
		add_var_to_env(*var, new_element);
		free(new_element);
	}
	print_env(var);
	return (1);
}
