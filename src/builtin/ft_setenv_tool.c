/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv_tool.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:23:43 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 17:59:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		print_env(t_var *var)
{
	while (var)
	{
		if (var->type == ENVIRONEMENT)
		{
			ft_printf("%s=", var->name);
			ft_printf("%s\n", var->data);
		}
		var = var->next;
	}
}

int			print_err_setenv(char **al)
{
	ft_free_tab(al);
	ft_printf_err("42sh: setenv:{B.T.red.} error{eoc}: Permission denied\n");
	return (1);
}
