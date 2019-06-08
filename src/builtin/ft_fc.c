/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fc.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 11:18:28 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 11:44:48 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

#define TERM "42sh"

void		determ_fc_flags(t_fc *fc, t_process *p, int k, int i)
{
	int		j;

	while (p->cmd[i] && ft_strlen(p->cmd[i]) > 1 && p->cmd[i][0] == '-' &&
			p->cmd[i][1] != '-')
	{
		j = 1;
		while (p->cmd[i][j] && ft_strchr(fc->flags_model, p->cmd[i][j]) != NULL)
		{
			if (ft_strchr(fc->flags, p->cmd[i][j]) == NULL)
				fc->flags[k++] = p->cmd[i][j];
			j++;
		}
		if (j < ft_strlen(p->cmd[i]))
		{
			ft_printf_err("%s: fc: -%c: invalid option\n", TERM, p->cmd[i][j]);
			write(2, "fc: usage: fc [-e ename] [-nlr] [first] [last]", 46);
			write(2, " or fc -s [pat=rep] [cmd]", 25);
			fc->error = 1;
			break ;
		}
		i++;
	}
}

void		init_fc_struct(t_fc *fc)
{
	fc->flags_model = ft_strdup("elnrs");
	fc->flags = ft_strnew(6);
	fc->ename = ft_strnew(0);
	fc->str_first = ft_strnew(0);
	fc->str_last = ft_strnew(0);
	fc->int_first = -1;
	fc->int_last = -1;
	fc->first_is_str = -1;
	fc->last_is_str = -1;
	fc->error = 0;
}

int			ft_fc(t_process *p, t_var **var)
{
	t_fc	fc;

	(void)var;
	init_fc_struct(&fc);
	determ_fc_flags(&fc, p, 0, 1);
	ft_printf("\nflags trouves --> /%s/\n", fc.flags);
//	if  (error == 0)
	return (0);
}
