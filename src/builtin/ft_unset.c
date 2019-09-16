/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unset.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 15:49:17 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 15:52:43 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int			ft_unset_var(char *name, t_var **ptr_var)
{
	if (remove_list_var(ptr_var, ENVIRONEMENT, name))
		return (1);
	else if (remove_list_var(ptr_var, LOCAL, name))
		return (1);
	return (0);
}

int			ft_unset(t_process *p, t_var **ptr_var)
{
	int i;

	i = 0;
	while (p->cmd[++i])
	{
		if (!(ft_unset_var(p->cmd[i], ptr_var)))
			ft_printf("{B.T.red.}%s{eoc} not found\n", p->cmd[i]);
	}
	stock(*ptr_var, 5);
	return (0);
}
