/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_spe_params.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/02 18:07:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 08:26:41 by vde-sain    ###    #+. /#+    ###.fr     */
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
	while (save->next)
		save = save->next;
	while (spe[i])
	{
		save->next = (t_var*)malloc(sizeof(t_var));
		save = save->next;
		save->name = ft_strnew(1);
		save->name[0] = spe[i];
		save->next = NULL;
		save->data = get_spe_param_data(spe[i], av, var);
		save->type = 4;
		i++;
	}
	ft_strdel(&spe);
}
