/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 13:34:01 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:35:30 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

static void	redirection_builtin_fd(int new, int old, t_process *p)
{
	if (old == 2)
		p->fd_error = new;
	if (old == 1)
		p->fd_out = new;
}

int			duplication_builtin(t_process *p, t_redirect *redirect, int fd_in,
			int fd_out)
{
	if (ft_strcmp(redirect->token, ">&") == 0)
	{
		if (ft_strcmp(redirect->fd_out, "-") == 0)
		{
			p->fd_out = -1;
			return (1);
		}
		else if (fd_in > 0 && fd_out > 0)
		{
			if (fd_in == 2)
				p->fd_error = (fd_out == 1) ? p->fd_out : fd_out;
			if (fd_in == 1)
				p->fd_out = (fd_out == 2) ? p->fd_error : fd_out;
		}
		else
			ft_printf_err("42sh: file number expected\n");
		return (0);
	}
	return (1);
}

static int	redirection_builtin_file(t_redirect *redirect, t_process *p)
{
	if (ft_strcmp(redirect->token, ">") == 0)
	{
		if (!fd_right(redirect->fd_out))
			return (0);
		redirection_builtin_fd(redirect->open_out, redirect->fd, p);
	}
	if (ft_strcmp(redirect->token, ">>") == 0)
	{
		if (!fd_right(redirect->fd_out))
			return (0);
		redirection_builtin_fd(redirect->open_out, redirect->fd, p);
	}
	return (1);
}

int			launch_redirection_builtin(t_process *p)
{
	t_redirect	*redirect;
	int			fd_in;
	int			fd_out;

	redirect = p->redirect;
	fd_in = 1;
	while (redirect)
	{
		fd_in = ft_atoi(redirect->fd_in);
		if (!redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(redirect->fd_out);
		if (redirection_builtin_file(redirect, p) == 0)
			return (0);
		if (duplication_builtin(p, redirect, fd_in, fd_out) == 0)
			return (0);
		redirect = redirect->next;
	}
	return (1);
}