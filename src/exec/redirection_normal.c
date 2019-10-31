/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_normal.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 17:20:57 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 11:01:34 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
/*
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
*/
void		redirection_fill_pos_fd(t_pos *pos, int old_fd, int new_fd)
{
	if (old_fd == 1)
		pos->act_fd_out = new_fd;
	if (pos->act_fd_out == 2 && pos->act_fd_error != 2)
		pos->act_fd_out = pos->act_fd_error;
	else if (old_fd == 2)
	{
		pos->act_fd_error = new_fd;
		if (pos->act_fd_error == 1 && pos->act_fd_out != 1)
			pos->act_fd_error = pos->act_fd_out;
	}
	to_stock(pos, 0);
}

void		normal_redirection_behavior(t_redirect *red, t_process *p,
			t_pos *pos, int is_builtin)
{
	int		new_fd_out;
	int		init_fd;
	char	*file;

	if (red->fd_out[0] != '/')
		file = ft_strdup("./");
	else
		file = ft_strnew(0);
	file = ft_strjoinf(file, red->fd_out, 1);
	new_fd_out = 1;
	init_fd = red->fd;
	if ((new_fd_out = redirection_get_argument_file_fd(red, file, p, 1)) == -1)
		return ;
	else if (is_builtin != 1)
	{
		if (ft_strcmp(red->token, "<") != 0)
			dup2(new_fd_out, red->fd);
		else
			dup2(new_fd_out, 0);
	}
	if (ft_strcmp(red->token, "<") != 0)
	redirection_fill_pos_fd(pos, init_fd, new_fd_out);
	else
		redirection_fill_pos_fd(pos, 0, new_fd_out);
	ft_strdel(&file);
}

void		heredoc_redirection_behavior(t_redirect *red, t_process *p,
			t_pos *pos)
{
	int		hdoc_file;

	(void)p;
	(void)pos;
	hdoc_file = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	write(hdoc_file, red->heredoc_content, ft_strlen(red->heredoc_content));
	write(hdoc_file, "\n", 1);
	hdoc_file = open("/tmp/heredoc", O_CREAT | O_RDWR, 0666);
	dup2(hdoc_file, 0);
	p->fd_in = 1;
	close(hdoc_file);
}
