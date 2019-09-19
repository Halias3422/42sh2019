/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 14:08:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 14:47:35 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		print_env(t_var *var)
{
	while (var)
	{
		if (var->type == ENVIRONEMENT)
		{
			ft_printf("%s=", var->name);
			ft_printf("%s\n", var->data);
		}
		var = var->next;
	}
}

void		add_setenv(t_var **var, char *name, char *data)
{
	t_var	*start;

	start = malloc(sizeof(t_var));
	start->name = name;
	start->data = data;
	start->type = ENVIRONEMENT;
	start->next = (*var);
	(*var) = start;
}

void		add_var_to_env(t_var **var, char *name, char *data)
{
	t_var	*prev;

	if (!(*var))
	{
		add_setenv(var, name, data);
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
		(*var) = malloc(sizeof(t_var));
		prev->next = (*var);
		(*var)->next = NULL;
		(*var)->name = name;
		(*var)->data = data;
		(*var)->type = ENVIRONEMENT;
		return ;
	}
	ft_strdel(&(*var)->data);
	ft_strdel(&name);
	(*var)->data = data;
}

// static int	element_already_exists_and_replace(char **element, t_var *var)
// {
// 	while (var != NULL && ft_strcmp(element[0], var->name) != 0)
// 		var = var->next;
// 	if (var == NULL)
// 		return (0);
// 	free(var->data);
// 	free(var->name);
// 	var->name = element[0];
// 	var->data = element[1];
// 	return (1);
// }

// static void	add_var_to_env(t_var *var, char **element)
// {
// 	t_var		*new;

// 	while (var->next != NULL)
// 		var = var->next;
// 	new = (t_var*)malloc(sizeof(t_var));
// 	new->name = element[0];
// 	new->data = element[1];
// 	new->type = ENVIRONEMENT;
// 	new->next = NULL;
// 	var->next = new;
// }

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
	char		*name;
	char		*data;

	if (p->cmd[1])
	{
		if (setenv_rules(p) == 0)
			return (0);
		name = init_name(p->cmd[1]);
		data = init_data(p->cmd[1]);
		add_var_to_env(var, name, data);
	// 	new_element = ft_strsplit(p->cmd[1], '=');
	// 	if ((new_element[1] && new_element[2]) || (new_element[0] == NULL &&
	// 				new_element[1] == NULL) || p->cmd[1][0] == '=')
	// 	{
	// 		ft_tabfree(new_element);
	// 		ft_printf("42sh: setenv: bad parameters, use -u for usage\n");
	// 		return (0);
	// 	}
	// 	if (element_already_exists_and_replace(new_element, *var) == 1)
	// 	{
	// 		free(new_element);
	// 		print_env(var);
	// 		return (1);
	// 	}
	// 	add_var_to_env(*var, new_element);
	// 	free(new_element);
	}
	print_env(*var);
	return (1);
}
