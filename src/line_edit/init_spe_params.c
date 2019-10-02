/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_spe_params.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/02 18:07:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 18:42:12 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

char		*get_spe_param_data(char c, char **av, t_var *var)
{
	if (c == '0')
		return (ft_strdup(av[0]));
	else if (c == '?')
		return (ft_strdup("0"));
	else if (c == '$')
		return (ft_itoa(getpid()));
	else if (c == '!')
		return (ft_strdup("0"));
	else if (c == '_')
		return (ft_strdup(ft_get_val("_", var, ENVIRONEMENT)));
	return (NULL);
}

void		init_spe_params(t_var *var, t_pos *pos, char **av)
{
	char	*spe;
	int		i;
	t_var	*save;

	save = var;
	i = 0;
	(void)pos;
	spe = ft_strdup("0?$!_");
	while (var->next)
		var = var->next;
	while (spe[i])
	{
		var->next = (t_var*)malloc(sizeof(t_var));
		var = var->next;
		var->name = ft_strnew(1);
		var->name[0] = spe[i];
		var->next = NULL;
		var->data = get_spe_param_data(spe[i], av, save);
		var->type = 4;
		ft_printf("var->data = %s\n", var->data);
		i++;
	}
//	while (save->next)
//	{
//		ft_printf("save->name = [%s] -- save->data = [%s] -- save->type = [%d]\n", save->name, save->data, save->type);
//		save = save->next;
//	}
	ft_strdel(&spe);
}
