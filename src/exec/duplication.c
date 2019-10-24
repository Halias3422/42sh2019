/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   duplication.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 13:34:01 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 08:48:58 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int	duplication_in(t_redirect *redirect, int fd_in, int fd_out)
{
	if (ft_strcmp(redirect->token, "<&") == 0)
	{
		if (ft_strcmp(redirect->fd_out, "-") == 0)
			close(fd_in);
		else if (fd_in > 0 && fd_out > 0)
		{
			if (fd_out > STDERR_FILENO)
				ft_printf_err("42sh: %d: bad file descriptor\n", fd_out);
			else if (dup2(fd_in, fd_out) == -1)
				ft_printf_err("42sh: duplication not working\n");
			else
				return (1);
		}
		else
			ft_printf_err("42sh: file number expected");
		return (0);
	}
	return (2);
}

int	duplication(t_redirect *redirect, int fd_in, int fd_out)
{
	if (ft_strcmp(redirect->token, ">&") == 0)
	{
		if (ft_strcmp(redirect->fd_out, "-") == 0)
		{
			close(fd_in);
			return (1);
		}
		else if (fd_in > 0 && fd_out > 0)
		{
			if (fd_out > STDERR_FILENO)
				ft_printf_err("42sh: %d: bad file descriptor\n", fd_out);
			else if (dup2(fd_out, fd_in) == -1)
				ft_printf_err("42sh: duplication not working\n");
			else
				return (1);
		}
		else
			ft_printf_err("42sh: file number expected\n");
		return (0);
	}
	return (duplication_in(redirect, fd_in, fd_out));
}
