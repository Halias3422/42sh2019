/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 15:27:39 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 10:04:20 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			ft_tabclen(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char		*ft_get_val(char *name, t_var *var, int type)
{
	while (var)
	{
		if (ft_strcmp(name, var->name) == 0 && var->type == type)
			return (var->data);
		var = var->next;
	}
	return (NULL);
}

/*
** pointeur su premier element
*/

void		remove_item_var(t_var **var)
{
	free((*var)->name);
	free((*var)->data);
	free(*var);
	*var = NULL;
}

int			remove_list_var(t_var **ptr_var, int type, char *name)
{
	t_var *var;
	t_var *buf;
	t_var *pres;

	var = *ptr_var;
	if (ft_strcmp(name, (var)->name) == 0 && (var)->type == type)
	{
		printf("ptr_var = %p && ptr_var->next = %p\n", *ptr_var, (*ptr_var)->next);
		buf = var->next;
		remove_item_var(&var);
		printf("var = %p\n", var);
		(*ptr_var) = buf;
		printf("buf = %p\n", buf);
		printf("fin ptr_var = %p\n", *ptr_var);
		return (1);
	}
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0 && var->type == type)
		{
			buf = var->next;
			remove_item_var(&var);
			pres->next = buf;
			return (1);
		}
		pres = var;
		var = var->next;
	}
	return (0);
}

void		add_list_env(t_var **ptr_var, int type, char *name, char *data)
{
	t_var *var;

	type = 0;
	var = *ptr_var;
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0)
		{
			free(var->data);
			var->data = data;
			return ;
		}
		var = var->next;
	}
}
