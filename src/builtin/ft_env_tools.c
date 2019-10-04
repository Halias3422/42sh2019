/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 10:31:09 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 13:58:06 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		add_list_env(t_var **ptr_var, int type, char *name, char *data)
{
	t_var	*var;
	t_var	*last;

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

t_var		*put_new_entry_in_var(t_var *var, char **new_env_entry,
		int usage)
{
	if (usage == 0)
		var = add_list_back_env(NULL);
	else if (usage == 1)
	{
		var->next = add_list_back_env(var);
		var = var->next;
	}
	var->name = ft_strdup(new_env_entry[0]);
	var->data = ft_strdup(new_env_entry[1]);
	var->type = ENVIRONEMENT;
	if (usage == 0)
		var->next = NULL;
	return (var);
}

void		free_new_env(t_var *head)
{
	t_var	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		tmp->data = ft_secure_free(tmp->data);
		tmp->name = ft_secure_free(tmp->name);
		free(tmp);
	}
}

t_var		*init_t_var(t_var *new)
{
	new->data = NULL;
	new->name = NULL;
	new->type = ENVIRONEMENT;
	new->next = NULL;
	return (new);
}

t_var		*add_list_back_env(t_var *env)
{
	t_var	*new;

	new = NULL;
	if (!(new = (t_var*)malloc(sizeof(t_var))))
		return (NULL);
	if (env == NULL)
	{
		init_t_var(new);
		return (new);
	}
	while (env->next != NULL)
		env = env->next;
	init_t_var(new);
	env->next = new;
	return (new);
}
