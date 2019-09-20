/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/12 13:09:07 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 14:17:53 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void	find_alias(t_process *p, t_var *var, int k)
{
	t_var	*tmp;

	tmp = var;
	while (tmp && ft_strcmp(p->cmd[k], tmp->name))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putstr("21sh: alias: ");
		ft_putstr(p->cmd[k]);
		ft_putstr(": not found\n");
		return ;
	}
	ft_putstr("alias ");
	ft_putstr(tmp->name);
	ft_putstr("='");
	ft_putstr(tmp->data);
	ft_putstr("'\n");
}

void		add_alias(t_var **var, char *name, char *data)
{
	t_var	*start;

	start = malloc(sizeof(t_var));
	start->name = name;
	start->data = data;
	start->type = ALIAS;
	start->next = (*var);
	(*var) = start;
}

void		add_list_alias(t_var **var, char *name, char *data)
{
	t_var	*prev;

	prev = NULL;
	if (!(*var))
	{
		add_alias(var, name, data);
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
		(*var)->type = ALIAS;
		return ;
	}
	ft_strdel(&(*var)->data);
	ft_strdel(&name);
	(*var)->data = data;
}

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

int		main_alias(t_process *p, t_var **var)
{
	char	*name;
	char	*data;
	int		i;
	int		k;

	k = 0;
	if (!p->cmd[1])
		return (print_alias(*var));
	while (p->cmd[++k])
	{
		i = 0;
		while (p->cmd[k][i] && p->cmd[k][i] != '=')
			i++;
		if (i == 0 || !p->cmd[k][i])
			find_alias(p, (*var), k);
		else
		{
			name = ft_strsub(p->cmd[k], 0, i);
			data = ft_strsub(p->cmd[k], i + 1, ft_strlen(p->cmd[k]) - (i + 1));
			add_list_alias(var, name, data);
		}
	}
	return (1);
}

int		error_unlias(char *str)
{
	ft_putstr("21sh: ");
	ft_putstr("unalias: ");
	ft_putstr(str);
	ft_putstr(": not found\n");
	return (1);
}

int		check_a(t_process *p, t_var **var)
{
	t_var	*start;
	t_var	*tmp;

	start = (*var);
	if (!p->cmd[1] || (ft_strcmp(p->cmd[1], "-a") != 0))
		return (0);
	while (start && start->type == ALIAS)
	{
		*var = start->next;
		ft_strdel(&start->data);
		ft_strdel(&start->name);
		free(start);
		start = *var;
	}
	while (*var)
	{
		if ((*var)->next && (*var)->next->type == ALIAS)
		{
			tmp = (*var)->next->next;
			ft_strdel(&(*var)->next->data);
			ft_strdel(&(*var)->next->name);
			free((*var)->next);
			(*var)->next = tmp;
		}
		else
			*var = (*var)->next;
	}
	stock(start, 5);
	return (1);
}

int		main_unalias(t_process *p, t_var **var)
{
	t_var	*start;
	t_var	*tmp;
	t_var	*last;
	int		k;

	k = 1;
	last = NULL;
	start = (*var);
	if (check_a(p, var) == 1)
		return (1);
	while (p->cmd[k])
	{
		if (*var && ft_strcmp(p->cmd[k], (*var)->name) == 0)
		{
			if (!(*var)->next)
			{
				ft_strdel(&(*var)->name);
				ft_strdel(&(*var)->data);
				free(*var);
				(*var) = NULL;
				return (1);
			}
			(*var) = (*var)->next;
			ft_strdel(&start->name);
			ft_strdel(&start->data);
			free(start);
			return (1);
		}
		while (*var && ft_strcmp(p->cmd[k], (*var)->name) != 0)
		{
			last = (*var);
			(*var) = (*var)->next;
		}
		if (!(*var))
			return (error_unlias(p->cmd[k]));
		last->next = (*var)->next;
		tmp = (*var);
		(*var) = start;
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->data);
		free(tmp);
		k++;
	}
	return (1);
}
