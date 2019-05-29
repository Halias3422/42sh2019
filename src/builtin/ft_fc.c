/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fc.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/29 07:01:01 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:22:58 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

#define MODEL_FC "elnrs"
#define TERM "42sh"

int			ft_fc(t_process *p, t_var **var)
{
	int		i;
	int		j;
	int		k;
	char	*flags;

	flags = ft_strnew(6);
	(void)var;
	k = 0;
	i = 1;
	while (p->cmd[i] && ft_strlen(p->cmd[i]) > 1 && p->cmd[i][0] == '-' && p->cmd[i][1] != '-')
	{
		j = 0;
		while (p->cmd[i][j] && ft_strchr(MODEL_FC, p->cmd[i][j]) != NULL)
		{
			if (ft_strchr(flags, p->cmd[i][j]) == NULL)
				flags[k++] = p->cmd[i][j];
			j++;
		}
		if (j < ft_strlen(p->cmd[i]))
		{
	//		ft_printf_err("%s: fc: -%s: invalid option\n", "42sh", p->cmd[i][j]);
			write(1, "fc: usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]", 72);
			break ;
		}
		i++;
	}
	ft_printf("\nflags trouves --> /%s/\n", flags);
	return (0);
}
