/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_normal_redirection.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/31 13:17:04 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 16:29:40 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void			init_fd_link(t_fd *new)
{
	new->old_fd = -1;
	new->new_fd = -1;
	new->is_builtin = 0;
	new->error = 0;
	new->token = NULL;
	new->next = NULL;
}

t_fd			*add_list_back_fd(t_fd *fd)
{
	t_fd		*new;
	t_fd		*head;

	new = NULL;
	if (!(new = (t_fd*)malloc(sizeof(t_fd))))
		return (NULL);
	if (fd == NULL)
	{
		init_fd_link(new);
		return (new);
	}
	head = fd;
	while (fd->next != NULL)
		fd = fd->next;
	init_fd_link(new);
	fd->next = new;
	return (head);
}

void			redirect_simple_left(t_fd *fd, t_redirect *red, t_process *p)
{
	fd->token = ft_strdup("<");
	if (red->fd_in)
	{
		fd->old_fd = ft_atoi(red->fd_in);
		if (fd->old_fd > 255)
		{
			ft_printf_err_fd("42sh: %s: Bad file descriptor\n", red->fd_in);
			fd->error = 1;
			p->exec_builtin = 0;
		}
	}
	fd->new_fd = redirection_find_file_fd(red->fd_out, red, p, fd);
	if (fd->new_fd == -1)
		return ;
}

void			redirect_simple_right(t_fd *fd, t_redirect *red, t_process *p)
{
	(void)p;
	fd->token = ft_strdup(">");
	fd->old_fd = red->fd;
	fd->new_fd = redirection_find_file_fd(red->fd_out, red, p, fd);
	if (fd->new_fd == -1)
		return ;
}
