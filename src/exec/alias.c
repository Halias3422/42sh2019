/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/12 13:09:07 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 09:42:01 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

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
	char	**al;
	int		i;
	int		k;

	k = 0;
	if (!p->cmd[1])
		return (print_alias(*var));
	while (p->cmd[++k])
	{
		al = malloc(sizeof(char *) * 3);
		al[2] = 0;
		al[0] = init_name(p->cmd[k]);
		al[1] = init_data(p->cmd[k]);
		remoove_quote(&al);
		i = 0;
		while (p->cmd[k][i] && p->cmd[k][i] != '=')
			i++;
		if (i == 0 || !p->cmd[k][i])
			find_alias(p, (*var), k);
		else
			add_list_alias(var, al[0], al[1]);
		ft_free_tab(al);
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

void	free_one(t_var *var)
{
	ft_strdel(&var->data);
	ft_strdel(&var->name);
	free(var);
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
		free_one(start);
		start = *var;
	}
	while (*var)
	{
		if ((*var)->next && (*var)->next->type == ALIAS)
		{
			tmp = (*var)->next->next;
			free_one((*var)->next);
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
	start = (*var);
	last = NULL;
	if (check_a(p, var) == 1)
		return (1);
	while (p->cmd[k])
	{
		if (*var && ft_strcmp(p->cmd[k], (*var)->name) == 0)
		{
			if (!(*var)->next)
			{
				free_one((*var));
				(*var) = NULL;
				return (1);
			}
			(*var) = (*var)->next;
			free_one(start);
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
		free_one(tmp);
		k++;
	}
	return (1);
}
