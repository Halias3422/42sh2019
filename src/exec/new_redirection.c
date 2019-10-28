/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 15:44:58 by vde-sain    ###    #+. /#+    ###.fr     */
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
		if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, "<") == 0
				|| ft_strcmp(red->token, ">&") == 0)
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
	int	new_fd_out;
	int		init_fd;
	char	*file;


	file = ft_strdup("./");
	file = ft_strjoinf(file, red->fd_out, 1);
	new_fd_out = 1;
	init_fd = red->fd;
	if ((new_fd_out = redirection_get_argument_file_fd(red, file, p)) == -1)
		return ;
	else if (is_builtin != 1)
		duping_fd_for_binaries(new_fd_out, red->fd);
	redirection_fill_pos_fd(pos, init_fd, new_fd_out);
	ft_strdel(&file);
}

void		aggregation_file_redirection(t_redirect *red, t_process *p,
			t_pos *pos, int is_builtin)
{
	char	*file;
	int		new_fd_out;
	int		new_fd_in;

	if (ft_strcmp(red->token, "<&") == 0 || (red->fd_in && is_all_num(red->fd_in) != 1))
	{
		ft_printf("42sh: %s: ambiguous redirect\n", red->fd_out);
		p->exec_builtin = 0;
	}
	if (red->fd_in)
	new_fd_in = ft_atoi(red->fd_in);
	else
		new_fd_in = 1;
	if (is_all_num(red->fd_out) != 1)
	{
		if (red->fd_out && red->fd_out[0] != '/')
			file = ft_strdup("./");
		else
			file = ft_strnew(0);
		file = ft_strjoinf(file, red->fd_out, 1);
		if ((new_fd_out = redirection_get_argument_file_fd(red, file, p)) == -1)
			return ;
	}
	else
		new_fd_out = ft_atoi(red->fd_out);
	if (new_fd_in == 1 || new_fd_out == 1)
		p->fd_in = new_fd_out;
	else
		p->fd_in = 1;
	if (ft_strcmp(red->token, "<&") == 0 && is_builtin != 1)
		duping_fd_for_binaries(new_fd_in, new_fd_out);
	else if (ft_strcmp(red->token, ">&") == 0 && is_builtin != 1)
	{

		duping_fd_for_binaries(new_fd_out, new_fd_in);
	}
	redirection_fill_pos_fd(pos, new_fd_in, new_fd_out);
	ft_strdel(&file);
}

void		aggregation_redirection_behavior(t_redirect *red, t_process *p,
			t_pos *pos, int is_builtin)
{
	int		ret;
	int		fd_in;
	int		fd_out;

	fd_in = ft_atoi(red->fd_in);
	fd_out = ft_atoi(red->fd_out);
	if (ft_strcmp(red->fd_out, "-") == 0)
	{
			p->exec_builtin = 0;
			return ;
	}
	if (fd_out != 1 && fd_out != 2 && (ret = isatty(fd_out) == 0))
	{
		ft_printf_err_fd("42sh: %s: Bad file descriptor\n", red->fd_out);
		if (test_builtin(p) != 1)
			close(fd_in);
		p->exec_builtin = 0;
	}
	else
	{
		if (fd_in == 1 || fd_out == 1)
			p->fd_in = fd_out;
		else
			p->fd_in = 1;
		if (ft_strcmp(red->token, "<&") == 0 && is_builtin != 1)
			duping_fd_for_binaries(fd_out, fd_in);
		else if (ft_strcmp(red->token, ">&") == 0 && is_builtin != 1)
			duping_fd_for_binaries(fd_out, fd_in);
		redirection_fill_pos_fd(pos, fd_in, fd_out);
	}
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
	hdoc_file = open("/tmp/heredoc", O_CREAT | O_RDWR , 0666);
		dup2(hdoc_file, 0);
	p->fd_in = 1;
	close(hdoc_file);
}

void		init_pipe_redirection(t_pos *pos, t_process *p, int is_builtin)
{
	if (pos->pipe > 0 && p->split != 'P')
	{
		pos->act_fd_out = 1;
		if (is_builtin != 1)
		{
			close(pos->pipe);
			dup2(p->fd_in, 0);
		}
	}
}

void		end_pipe_redirection(t_pos *pos, t_process *p, int is_builtin,
			int check)
{
	if (p->split == 'P')
	{
		pos->act_fd_out = p->fd_out;
		if (is_builtin != 1 && check > 0)
			dup2(p->fd_out, p->fd_in);
		else if (is_builtin != 1)
			dup2(p->fd_out, 1);
	}

}

void		get_all_redirections_done(t_process *p, t_pos *pos, t_redirect *red)
{
	int			is_builtin;
	int			check;
	
	check = 0;
	is_builtin = test_builtin(p);
	init_pipe_redirection(pos, p, is_builtin);
	while (red)
	{
		check++;
		if (ft_strcmp(red->token, "<") == 0 || ft_strcmp(red->token, ">") == 0
				|| ft_strcmp(red->token, ">>") == 0)
			normal_redirection_behavior(red, p, pos, is_builtin);
		else if (ft_strcmp(red->token, "<<") == 0)
			heredoc_redirection_behavior(red, p, pos);
		else if ((ft_strcmp(red->token, "<&") == 0 ||
				ft_strcmp(red->token, ">&") == 0) &&
				is_all_num(red->fd_out) == 1 && (!red->fd_in ||
					is_all_num(red->fd_in) == 1))
			aggregation_redirection_behavior(red, p, pos, is_builtin);
		else if (ft_strcmp(red->token, "<&") == 0 ||
				ft_strcmp(red->token, ">&") == 0)
			aggregation_file_redirection(red, p, pos, is_builtin);
		red = red->next;
	}
	end_pipe_redirection(pos, p, is_builtin, check);
}
