/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 19:51:39 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <fcntl.h>

//
// ne pas oublier de close file
//
void		duping_fd_for_binaries(int fd1, int fd2)
{
	dup2(fd1, fd2);
}

int			redirection_get_argument_file_fd(t_redirect *red, char *file,
			t_process *p)
{
	int		new_fd_out;

	new_fd_out = 1;
	if (access(file, F_OK) != -1 && access(file, W_OK) != -1)
	{
		if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, "<") == 0)
		new_fd_out = open(file, O_RDWR | O_TRUNC);
		else if (ft_strcmp(red->token, ">>") == 0)
		{
			new_fd_out = open(file, O_WRONLY | O_CREAT |O_APPEND);
		}
	}
	else if (access(file, F_OK) != -1 && access(file, W_OK) == -1)
		ft_printf_err_fd("42sh: %s: permission denied\n", red->fd_out);
	else if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">>") == 0
			|| ft_strcmp(red->token, ">&") == 0)
		new_fd_out = open(file, O_RDWR | O_CREAT, 0666);
	else
	{
		ft_printf_err_fd("42sh: %s: No such file or directory\n", red->fd_out);
		p->exec_builtin = 0;
		ft_strdel(&file);
		return (-1);
	}
	return (new_fd_out);
}

void		redirection_fill_pos_fd(t_pos *pos, int old_fd, int new_fd)
{
	if (old_fd == 1)
		pos->act_fd_out = new_fd;
	else if (old_fd == 2)
		pos->act_fd_error = new_fd;
	to_stock(pos, 0);
}

void		normal_redirection_behavior(t_redirect *red, t_process *p,
			t_pos *pos)
{
	int	new_fd_out;
	int		init_fd;
	char	*file;


	file = ft_strdup("./");
	file = ft_strjoinf(file, red->fd_out, 1);
	new_fd_out = 1;
	init_fd = red->fd;
	if ((new_fd_out = redirection_get_argument_file_fd(red, file, p)) == -1)
		return ;
	if (ft_strcmp(red->token, "<<") == 0)
		duping_fd_for_binaries(red->fd, 1);
	else if (test_builtin(p) != 1)
		duping_fd_for_binaries(new_fd_out, red->fd);
	redirection_fill_pos_fd(pos, init_fd, new_fd_out);
	ft_strdel(&file);
}

void		aggregation_file_redirection(t_redirect *red, t_process *p,
			t_pos *pos)
{
	char	*file;
	int		new_fd_out;
	int		new_fd_in;

	if (ft_strcmp(red->token, "<&") == 0)
	{
		ft_printf("42sh: %s: ambiguous redirect\n", red->fd_out);
		p->exec_builtin = 0;
	}
	if (is_all_num(red->fd_in) != 1)
		new_fd_in = 1;
	else
		new_fd_in = ft_atoi(red->fd_in);
	if (red->fd_out && red->fd_out[0] != '/')
		file = ft_strdup("./");
	else
		file = ft_strnew(0);
	file = ft_strjoinf(file, red->fd_out, 1);
	if ((new_fd_out = redirection_get_argument_file_fd(red, file, p)) == -1)
		return ;
	if (ft_strcmp(red->token, "<&") == 0)
		duping_fd_for_binaries(new_fd_in, new_fd_out);
	else if (ft_strcmp(red->token, ">&") == 0)
		duping_fd_for_binaries(new_fd_out, new_fd_in);
	redirection_fill_pos_fd(pos, new_fd_in, new_fd_out);
	ft_strdel(&file);
}

void		aggregation_redirection_behavior(t_redirect *red, t_process *p,
			t_pos *pos)
{
	int		ret;
	int		fd_in;
	int		fd_out;

		fd_in = ft_atoi(red->fd_in);
		fd_out = ft_atoi(red->fd_out);
		if ((ret = isatty(fd_out) == 0))
		{
			ft_printf_err_fd("42sh: %s: Bad file descriptor\n", red->fd_out);
			if (test_builtin(p) != 1)
				close(fd_in);
			p->exec_builtin = 0;
		}
		else
		{
			if (ft_strcmp(red->token, "<&") == 0)
				duping_fd_for_binaries(fd_out, fd_in);
			else if (ft_strcmp(red->token, ">&") == 0)
				duping_fd_for_binaries(fd_out, fd_in);
			redirection_fill_pos_fd(pos, fd_in, fd_out);
		}
}

void		get_all_redirections_done(t_process *p)
{
	t_redirect	*red;
	t_pos		*pos;

	pos = to_stock(NULL, 1);
	red = p->redirect;
	if (red && red->token)
	while (red)
	{
		if (ft_strcmp(red->token, "<") == 0 || ft_strcmp(red->token, ">") == 0
				|| ft_strcmp(red->token, ">>") == 0)
			normal_redirection_behavior(red, p, pos);
		else if ((ft_strcmp(red->token, "<&") == 0 ||
				ft_strcmp(red->token, ">&") == 0) &&
				is_all_num(red->fd_out) == 1)
			aggregation_redirection_behavior(red, p, pos);
		else if (ft_strcmp(red->token, "<&") == 0 ||
				ft_strcmp(red->token, ">&") == 0)
			aggregation_file_redirection(red, p, pos);
		red = red->next;
	}
}
