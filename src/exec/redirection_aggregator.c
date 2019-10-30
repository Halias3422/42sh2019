/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_aggregator.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 17:19:24 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 16:04:15 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		finishing_aggregation_file(t_redirect *red, t_process *p,
			int new_fd_in, int new_fd_out)
{
	int		is_builtin;
	t_pos	*pos;

	pos = to_stock(NULL, 1);
	is_builtin = test_builtin(p);
	if (new_fd_in == 1 || new_fd_out == 1)
		p->fd_in = new_fd_out;
	else
		p->fd_in = 1;
	if (ft_strcmp(red->token, "<&") == 0 && is_builtin != 1)
		dup2(new_fd_in, new_fd_out);
	else if (ft_strcmp(red->token, ">&") == 0 && is_builtin != 1)
	{
		dprintf(2, "new_fd_out = %d new_fd_in = %d\n", new_fd_out, new_fd_in);
		dup2(new_fd_out, new_fd_in);
		}
	redirection_fill_pos_fd(pos, new_fd_in, new_fd_out);
}

void		aggregation_file_redirection(t_redirect *red, t_process *p,
			char *file)
{
	int		new_fd_in;
	int		new_fd_out;

	if (ft_strcmp(red->token, "<&") == 0 ||
			(red->fd_in && is_all_num(red->fd_in) != 1))
	{
		ft_printf_err_fd("42sh: %s: ambiguous redirect\n", red->fd_out);
		p->exec_builtin = 0;
	}
	new_fd_in = (red->fd_in) ? ft_atoi(red->fd_in) : 1;
	if (is_all_num(red->fd_out) != 1)
	{
		if (red->fd_out && red->fd_out[0] != '/')
			file = ft_strdup("./");
		else
			file = ft_strnew(0);
		file = ft_strjoinf(file, red->fd_out, 1);
		if ((new_fd_out = redirection_get_argument_file_fd(red, file, p, 1))
				== -1)
			return ;
		ft_strdel(&file);
	}
	else
		new_fd_out = ft_atoi(red->fd_out);
	finishing_aggregation_file(red, p, new_fd_in, new_fd_out);
}

void		finishing_aggregation_redirection(int fd_in, int fd_out,
			t_redirect *red, t_process *p)
{
	int		is_builtin;
	t_pos	*pos;

	is_builtin = test_builtin(p);
	pos = to_stock(NULL, 1);
	if (fd_in == 1 && fd_out == 1 && is_builtin != 1)
		p->fd_in = fd_out;
	if (ft_strcmp(red->token, "<&") == 0 && is_builtin != 1)
		dup2(fd_out, fd_in);
	else if (ft_strcmp(red->token, ">&") == 0 && is_builtin != 1)
	{
		dup2(fd_out, fd_in);
		dprintf(2, "je redirige fd_out = %d fd_in = %d\n", fd_out, fd_in);
	}
	redirection_fill_pos_fd(pos, fd_in, fd_out);
	dprintf(2, "pos->act_fd_out ici = %d\n", pos->act_fd_out);
}

void		aggregation_minus_behavior(t_redirect *red, int fd_in, t_pos *pos,
			int is_builtin)
{
		if (is_builtin != 1)
			close(fd_in);
		else if (is_builtin == 1 && ft_strcmp(red->fd_in, "1") == 0)
			pos->act_fd_out = -1;
		else if (is_builtin == 1 && ft_strcmp(red->fd_in, "2") == 0)
			pos->act_fd_error = -1;
}

void		aggregation_redirection_behavior(t_redirect *red, t_process *p)
{
	int		ret;
	int		fd_in;
	int		fd_out;
	t_pos	*pos;
	int		is_builtin;

	is_builtin = test_builtin(p);
	pos = to_stock(NULL, 1);
	fd_in = ft_atoi(red->fd_in);
	fd_out = ft_atoi(red->fd_out);
	if (ft_strcmp(red->fd_out, "-") == 0)
		return (aggregation_minus_behavior(red, fd_in, pos, test_builtin(p)));
	if (fd_out != 1 && fd_out != 2 && (ret = isatty(fd_out) == 0))
	{
		ft_printf_err_fd("42sh: %s: Bad file descriptor\n", red->fd_out);
		if (test_builtin(p) != 1)
			close(fd_in);
		p->exec_builtin = 0;
	}
	else
		finishing_aggregation_redirection(fd_in, fd_out, red, p);
	dprintf(2, "p->fd_out = %d fd_out = %d\n", p->fd_out, fd_out);
//	p->fd_out = fd_out;
	if ((ft_strcmp(red->token, ">&") == 0 && fd_out == 1) || (ft_strcmp(red->token, "<&") == 0 && fd_in == 1))
	p->fd_in = fd_in;
}
