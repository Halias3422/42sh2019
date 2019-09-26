/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_echo.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 15:00:57 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/26 14:30:02 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int		ft_echo_simple(t_process *p, t_var **var)
{
	int i;

	i = 1;
	var = NULL;
	while (p->cmd[i] != NULL)
	{
		if (i != 1)
			ft_putchar_fd(' ', p->fd_out);
		ft_putstr_fd(p->cmd[i], p->fd_out);
		i++;
	}
	ft_putchar_fd('\n', p->fd_out);
	return (1);
}

int		ft_echo_no_line(t_process *p, t_var **var)
{
	int i;

	i = 2;
	var = NULL;
	while (p->cmd[i] != NULL)
	{
		if (i != 2)
			ft_putchar_fd(' ', p->fd_out);
		ft_putstr_fd(p->cmd[i], p->fd_out);
		i++;
	}
	return (1);
}

int		ft_echo(t_process *p, t_var **var)
{
	if (p->fd_in < 0)
	{
		ft_printf("42sh: echo: write error: Bad file descriptor\n");
		return (1);
	}
	if (p->cmd[1])
	{
		if (ft_strcmp(p->cmd[1], "-n") == 0)
			return (ft_echo_no_line(p, var));
	}
	return (ft_echo_simple(p, var));
}
