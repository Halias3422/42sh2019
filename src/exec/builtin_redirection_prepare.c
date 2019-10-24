/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_redirection_prepare.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 12:57:40 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 12:57:58 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			is_all_num(char *str)
{
	int		i;

	i = 0;
	if (str[0] && str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		else
			i++;
	}
	return (1);
}

int			check_fd_out_content_before_redirection(t_process *p,
			t_redirect *redirect)
{
	if (ft_strcmp(redirect->token, "<&") == 0 &&
				is_all_num(redirect->fd_out) == 0)
	{
		p->fd_out = -1;
		ft_printf_err("42sh: file number expected\n");
		return (0);
	}
	else if (ft_strcmp("-", redirect->fd_out) == 0)
	{
		p->fd_out = -9;
		return (0);
	}
	return (1);
}
