/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/12 13:09:07 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 10:11:59 by mjalenqu    ###    #+. /#+    ###.fr     */
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

void	add_list_alias(t_var **var, char *name, char *data)
{
	t_var	*start;
	t_var	*tmp;

	start = (*var);
	tmp = NULL;
	while ((*var) && ft_strcmp((*var)->name, name) != 0)
	{
		tmp = (*var);
		(*var) = (*var)->next;
	}
	if ((*var))
	{
		ft_strdel(&(*var)->data);
		(*var)->data = ft_strdup(data);
		(*var) = start;
		return ;
	}
	(*var) = tmp;
	(*var)->next = malloc(sizeof(t_var));
	(*var)->next->name = ft_strdup(name);
	(*var)->next->data = ft_strdup(data);
	(*var)->next->type = ALIAS;
	(*var)->next->next = NULL;
	(*var) = start;
}

int		main_alias(t_process *p, t_var **var)
{
	char	*name;
	char	*data;
	int		i;
	int		k;

	k = 0;
	if (!p->cmd[1])
		return (1);
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
			ft_strdel(&data);
			ft_strdel(&name);
		}
	}
	stock(*var, 5);
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

void	delete_alias(t_var **var)
{
	t_var *prev;
	t_var *next;

	prev = NULL;
	while (*var)
	{
		next = (*var)->next;
		if ((*var)->type == ALIAS)
		{
			ft_strdel(&(*var)->data);
			ft_strdel(&(*var)->name);
			if (prev)
				prev->next = next;
			free(*var);
		}
		else
			prev = (*var);
		(*var) = next;
	}
}

int		main_unalias(t_process *p, t_var **var)
{
	t_var	*start;
	t_var	*tmp;
	t_var	*last;
	int		k;

	k = 1;
	start = (*var);
	while (p->cmd[k])
	{
		if (ft_strcmp(p->cmd[k], "-a") == 0)
		{
			delete_alias(var);
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
