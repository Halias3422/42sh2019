/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_echo.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 15:00:57 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 16:53:52 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int		ft_echo_simple(t_process *p)
{
	int i;

	i = 1;
	while (p->cmd[i] != NULL)
	{
		if (i != 1)
			ft_putchar_fd(' ', p->fd_out);
		ft_putstr_fd(p->cmd[i], p->fd_out);
		i++;
	}
	ft_putchar_fd('\n', p->fd_out);
	return (0);
}

int		ft_echo_no_line(t_process *p)
{
	int i;

	i = 2;
	while (p->cmd[i] != NULL)
	{
		if (i != 2)
			ft_putchar_fd(' ', p->fd_out);
		ft_putstr_fd(p->cmd[i], p->fd_out);
		i++;
	}
	return (0);
}

int		ft_echo(t_process *p, t_var **var)
{
	stock(*var, 5);
	if (p->cmd[1])
	{
		if (ft_strcmp(p->cmd[1], "-n") == 0)
			return (ft_echo_no_line(p));
	}
	return (ft_echo_simple(p));
}
