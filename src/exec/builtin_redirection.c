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
	printf("%d | %d\n", new, old);
	if (old == 2)
		p->fd_error = new;
	if (old == 1)
		p->fd_out = new;
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
		redirect = redirect->next;
	}
	return (1);
}
