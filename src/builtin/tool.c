/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 15:27:39 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 17:38:13 by rlegendr    ###    #+. /#+    ###.fr     */
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
		buf = (*ptr_var)->next;
		remove_item_var(ptr_var);
		(*ptr_var) = buf;
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

void		free_name_and_data(char *name, char *data)
{
	ft_strdel(&name);
	ft_strdel(&data);
}

void        add_list_env(t_var **ptr_var, int type, char *name, char *data)
{
    t_var    *var;
    t_var    *last;

    var = *ptr_var;
    if (!var)
        return ;
    while (var != NULL)
    {
        if (ft_strcmp(name, var->name) == 0 && type == var->type)
        {
            ft_strdel(&var->data);
            var->data = ft_strdup(data);
            free_name_and_data(name, data);
            return ;
        }
        if (var->next == NULL)
            last = var;
        var = var->next;
    }
    last->next = malloc(sizeof(t_var));
    last->next->name = ft_strdup(name);
    last->next->data = ft_strdup(data);
    last->next->type = type;
    last->next->next = NULL;
    free_name_and_data(name, data);
}
