/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_new_redirection.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 19:07:24 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 14:32:31 by rlegendr    ###    #+. /#+    ###.fr     */
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
	if (!(new = (t_fd*)ft_malloc(sizeof(t_fd))))
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
	char		*file;

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

void			redirect_simple_right(t_fd *fd, t_redirect *red, t_process *p)
{
	char		*file;

	(void)p;
	fd->token = ft_strdup(">");
	fd->old_fd = red->fd;
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
	ft_printf("je suis toujours vivant\n");
	ft_strdel(&file);
}

void			final_change_fd_for_redirections(t_fd *fd, t_pos *pos)
{
	while (fd)
	{
//		ft_printf("fd->old_fd = %d fd->new_fd = %d\n", fd->old_fd, fd->new_fd);
		if (fd->is_builtin == 0 && fd->error == 0)
		{
			if (ft_strcmp(fd->token, "<") == 0 && fd->old_fd == -1)
				dup2(fd->new_fd, 0);
			else if (ft_strcmp(fd->token, "<") == 0)
			{
				ft_printf("je redirige dans le dup\n");
				dup2(fd->old_fd, fd->new_fd);
			}
			if (ft_strcmp(fd->token, ">") == 0)
				dup2(fd->new_fd, fd->old_fd);
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

void			print_all_my_fkin_data(t_process *p, t_pos *pos, t_redirect *red, t_fd *head)
{
	int		i;

	i = 0;
	if (!p)
		ft_printf("{T.red.}process est NULL\n");
	if (!pos)
		ft_printf("{T.red.}pos est NULL\n");
	if (!red)
		ft_printf("{T.red.}red est NULL\n");
	if (!head)
		ft_printf("{T.red.}head est NULL\n");
	if (p && pos)
	{
		ft_printf("\n/////////// Debut ////////////\n");
		ft_printf("\n===== Process =====\n");
		while (p)
		{
			i = 0;
			ft_printf("p->cmd = [");
			while (p->cmd[i])
				ft_printf("%s ", p->cmd[i++]);
			ft_printf("]\n");
			ft_printf("pid = [%d]\nstatus = [%c](%d)\nsplit = [%c](%d)\nret = [%d]\ncompleted = %d\nstoped = [%d]\nbuiltin = [%d]\nfd_in = [%d]\nfd_out = [%d]\nfd_error = [%d]\nfile_in = [%d]\nfile_out = [%d]\nbackground = [%d]\nhash_error = [%s]\nexec_builtin = [%d]\n", p->pid, p->status, p->status, p->split, p->split, p->ret, p->completed, p->stoped, p->builtin, p->fd_in, p->fd_out, p->fd_error, p->file_in, p->file_out, p->background, p->hash_error, p->exec_builtin);
			if (p->redirect)
				ft_printf("\n	----- Redirection -----\n");
			while (p->redirect)
			{
				ft_printf("	fd_in = [%s]\n	fd_out = [%s]\n	heredoc_content = [%s]\n	fd = [%d]\n	open_in = [%d]\n	open_out = [%d]\n	token = [%s]\n", p->redirect->fd_in , p->redirect->fd_out, p->redirect->heredoc_content, p->redirect->fd, p->redirect->open_in, p->redirect->open_out, p->redirect->token);
				if (p->redirect->next == NULL)
					ft_printf("	-----------------------\n");
				p->redirect = p->redirect->next;
			}
			p = p->next;
		ft_printf("===================\n");
		}
		ft_printf("\n///////////  Fin  ////////////\n");
	}
	ft_printf("fin de fonction d imprpession\n");
}

void			got_a_pipe(t_process *p, t_pos *pos, t_redirect *red, t_fd *head)
{
	ft_printf("avant print\n");
	print_all_my_fkin_data(p, pos, red, head);
	ft_printf("apres print\n");
}

void			get_all_redirections_done(t_process *p, t_pos *pos, t_redirect
				*red, int is_builtin)
{
	t_fd		*fd;
	t_fd		*head;

//	ft_printf("p->cmd = [%T]\n", p->cmd);
	(void)p;
	fd = NULL;
	head = NULL;
//		got_a_pipe(p, pos, red, head);
	while (red)
	{
		fd = add_list_back_fd(fd);
		if (head == NULL)
			head = fd;
		while (fd->next)
			fd = fd->next;
		fd->is_builtin = is_builtin;
		if (ft_strcmp(red->token, "<") == 0)
			redirect_simple_left(fd, red, p);
		else if (ft_strcmp(red->token, ">") == 0)
			redirect_simple_right(fd, red, p);
		red = red->next;
	}
	final_change_fd_for_redirections(head, pos);
//	ft_printf("avant verif p split et split = [%c](%d)\n", p->split, p->split);
//	if (p->split == 'P')

//	ft_printf("pos->act_fd_out = %d pos->act_fd_error = %d\n", pos->act_fd_out, pos->act_fd_error);
}
