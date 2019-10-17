/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 07:42:30 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 17:02:13 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int			get_value_of_cmd_return(t_fc fc, t_var *var)
{
	if (ft_strchr(fc.flags, 's') == NULL && ft_strchr(fc.flags, 'e') == NULL)
		return (0);
	while (var && ft_strcmp(var->name, "?") != 0)
		var = var->next;
	if (var && ft_strcmp(var->name, "?") == 0)
		return (ft_atoi(var->data));
	return (0);
}

void		free_fc_struct(t_fc *fc)
{
	ft_strdel(&fc->flags_model);
	ft_strdel(&fc->flags);
	ft_strdel(&fc->str_first);
	ft_strdel(&fc->str_last);
}
