/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/12 13:09:07 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 09:54:59 by mjalenqu    ###    #+. /#+    ###.fr     */
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

	printf("add var = %p\n", *var);
	start = (*var);
	tmp = NULL;
	while ((*var) && ft_strcmp((*var)->name, name) != 0)
	{
		tmp = (*var);
		(*var) = (*var)->next;
	}
	if ((*var) && (*var)->type == ALIAS)
	{
		ft_strdel(&(*var)->data);
		(*var)->data = ft_strdup(data);
		(*var) = start;
		return ;
	}
	if (tmp)
	{
		(*var) = tmp;
		(*var)->next = malloc(sizeof(t_var));
		(*var) = (*var)->next;
	}
	else
		(*var) = malloc(sizeof(t_var));
	(*var)->name = ft_strdup(name);
	(*var)->data = ft_strdup(data);
	(*var)->type = ALIAS;
	(*var)->next = NULL;
	printf("var = %p\tvar->next = %p\n", *var, (*var)->next);
	if (start)
		(*var) = start;
	printf("debut = %p\n", *var);
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

int		check_first_alias(t_var **var, char *str)
{
	if (ft_strcmp(str, (*var)->name) == 0 && (*var)->type == ALIAS)
	{
		if (!(*var)->next)
		{
			ft_strdel(&(*var)->name);
			ft_strdel(&(*var)->data);
			free(*var);
			(*var) = NULL;
			stock((*var), 5);
			return (1);
		}
	}
	return (0);
}

/*
** si unalias le premier ou juste un alias dans var -> crash
*/

int		main_unalias(t_process *p, t_var **var)
{
	t_var	*prev;
	t_var	*next;
	t_var	*start;
	int		k;

	k = 1;
	start = (*var);
	prev = NULL;
	while (p->cmd[k])
	{
		if (ft_strcmp(p->cmd[k], "-a") == 0)
		{
			delete_alias(var);
			return (1);
		}
		if (check_first_alias(var, p->cmd[k]) == 1)
			return (1);
		while ((*var) && ft_strcmp(p->cmd[k], (*var)->name) != 0)
		{
			prev = (*var);
			(*var) = (*var)->next;
		}
		if (!(*var))
			return (error_unlias(p->cmd[k]));
		next = (*var)->next;
		if (prev != NULL)
			prev->next = next;
		ft_strdel(&(*var)->name);
		ft_strdel(&(*var)->data);
		free(*var);
		(*var) = start;
		k++;
	}
	stock((*var), 5);
	return (1);
}
/*
int		main_unalias(t_process *p, t_var **var)
{
	t_var	*start;
	// t_var	*tmp;
	t_var	*last;
	int		k;

	k = 1;
	start = (*var);
	while (p->cmd[k])
	{
		puts("1");
		if (ft_strcmp(p->cmd[k], "-a") == 0)
		{
			delete_alias(var);
			return (1);
		}
		puts("2");
		if (check_first_alias(var, p->cmd[k]) == 1)
			return (1);
		puts("3");
		while (*var && ft_strcmp(p->cmd[k], (*var)->name) != 0)
		{
			last = (*var);
			(*var) = (*var)->next;
		}
		puts("4");
		if (!(*var))
			return (error_unlias(p->cmd[k]));
		puts("5");
		// printf("last = %p\tlast->next = %p\n", last, last->next);
		// printf("var = %p\tvar->next = %p\n", *var, (*var)->next);
		if (last && *var && last->next && (*var)->next)
			last->next = (*var)->next;
		puts("6");
		ft_strdel(&(*var)->name);
		puts("7");
		ft_strdel(&(*var)->data);
		puts("8");
		free(*var);
		puts("9");
		(*var) = start;
		puts("10");
		k++;
	}
	stock(*var, 5);
	return (1);
}
*/