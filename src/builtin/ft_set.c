/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_set.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 17:13:59 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:01:35 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

// Changer pour ft_printf
// afficher charactere entre ''
// faire le tri

int		ft_set(t_process *p, t_var **ptr_var)
{
	t_var *var;

	var = *ptr_var;
	if (p->cmd[1])
		return (1);
	while (var)
	{
		ft_printf("%s=%s\n", var->name, var->data);
		var = var->next;
	}
	return (1);
}
