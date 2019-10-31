/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_new_redirection.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 19:07:24 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 11:05:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			redirection_get_argument_file_fd(t_redirect *red, char *file,
			t_process *p, int new_fd_out)
{
	if (access(file, F_OK) != -1 && access(file, W_OK) != -1)
	{
		if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">&") == 0)
			new_fd_out = open(file, O_RDWR | O_TRUNC);
		else if (ft_strcmp(red->token, "<") == 0)
			new_fd_out = open(file, O_RDWR | O_CREAT, 0666);
		else if (ft_strcmp(red->token, ">>") == 0)
			new_fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	else if (access(file, F_OK) != -1 && access(file, W_OK) == -1)
		ft_printf_err_fd("42sh: %s: permission denied\n", red->fd_out);
	else if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">>") == 0
			|| ft_strcmp(red->token, ">&") == 0)
	{
		new_fd_out = open(file, O_RDWR | O_CREAT, 0666);
	}
	else
	{
		ft_printf_err_fd("42sh: %s: No such file or directory\n", red->fd_out);
		p->exec_builtin = 0;
		ft_strdel(&file);
		return (-1);
	}
	return (new_fd_out);
}

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

void			redirect_simple_left(t_fd *fd, t_redirect *red, t_pos *pos,
				t_process *p)
{
	char		*file;

	fd->token = ft_strdup("<");
	ft_printf(" ICI redirect->fd_in = %s redirect->fd_out = %s redirect->fd = %d\n", red->fd_in, red->fd_out, red->fd);
	(void)pos;
	if (red->fd_in)
	fd->old_fd = ft_atoi(red->fd_in);
	if (red->fd_out[0] != '/')
		file = ft_strdup("./");
	else
		file = ft_strnew(0);
	file = ft_strjoinf(file, red->fd_out, 1);
	if ((fd->new_fd = redirection_get_argument_file_fd(red, file, p, 1)) == -1)
	{
		fd->error = 1;
		return ;
	}
	ft_strdel(&file);
}

void			final_change_fd_for_redirections(t_fd *fd, t_pos *pos)
{
	while (fd)
	{
		ft_printf("fd->old_fd = %d fd->new_fd = %d\n", fd->old_fd, fd->new_fd);
		if (fd->is_builtin == 0 && fd->error == 0)
		{
			if (ft_strcmp(fd->token, "<") == 0 && fd->old_fd == -1)
				dup2(fd->new_fd, 0);
			else
				dup2(fd->old_fd, fd->new_fd);
		}
		else if (fd->is_builtin == 1 && fd->error == 0)
		{
			if (fd->old_fd == 1)
				pos->act_fd_out = fd->new_fd;
			if (fd->old_fd == 2)
				pos->act_fd_out = fd->new_fd;
		}
		fd = fd->next;
	}
}

// revoir comportement de < 1. "cat < Makefile" 2. "cat 1<Makefile" 3. "cat toto<Makefile"

void			get_all_redirections_done(t_process *p, t_pos *pos, t_redirect
				*red, int is_builtin)
{
	t_fd		*fd;
	t_fd		*head;

	ft_printf("p->cmd = [%T]\n", p->cmd);
	(void)p;
	fd = NULL;
	head = NULL;
	while (red)
	{
		fd = add_list_back_fd(fd);
		if (head == NULL)
			head = fd;
		while (fd->next)
			fd = fd->next;
		fd->is_builtin = is_builtin;
		if (ft_strcmp(red->token, "<") == 0)
			redirect_simple_left(fd, red, pos, p);
		red = red->next;
	}
	final_change_fd_for_redirections(head, pos);
	ft_printf("pos->act_fd_out = %d pos->act_fd_error = %d\n", pos->act_fd_out, pos->act_fd_error);
}
