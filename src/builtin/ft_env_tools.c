/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 10:31:09 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 10:34:46 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

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
