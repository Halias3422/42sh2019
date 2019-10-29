/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 12:49:53 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <fcntl.h>

int			is_all_num(char *str)
{
	int		i;

	i = 0;
	if (str[0] && str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		else
			i++;
	}
	return (1);
}

static void		end_pipe_redirection(t_pos *pos, t_process *p, int is_builtin)
{
	if (pos->pipe > 0)
	{
		pos->act_fd_out = 1;
		if (is_builtin != 1)
		{
			close(pos->pipe);
			dup2(p->fd_in, 0);
		}
	}
}

static void		init_pipe_redirection(t_pos *pos, t_process *p, int is_builtin,
				int check)
{
	if (p->split == 'P')
	{
		if (!p->redirect || (p->redirect && (p->redirect->fd_in &&
		ft_strcmp(p->redirect->fd_in, "1") == 0 &&
		ft_strcmp(p->redirect->fd_out, "1") == 0)))
			pos->act_fd_out = p->fd_out;
		else if (p->redirect && p->redirect->fd_in &&
		ft_strcmp(p->redirect->fd_in, "1") == 0 &&
		ft_strcmp(p->redirect->fd_out, "1") != 0)
			pos->act_fd_out = ft_atoi(p->redirect->fd_out);
		else if (p->redirect && p->redirect->fd_in &&
		ft_strcmp(p->redirect->fd_in, "2") == 0 &&
		ft_strcmp(p->redirect->fd_out, "2") != 0)
			pos->act_fd_error = p->fd_out;
		if (is_builtin != 1 && check > 0)
			dup2(p->fd_out, p->fd_in);
		else if (is_builtin != 1)
			dup2(p->fd_out, 1);
	}
}

void			print_all_redirect(t_process *p)
{
	t_redirect	*red;

	red = p->redirect;
	if (!p)
		dprintf(2, "p est NULL\n");
	else
	{
		dprintf(2, "\n\n=======================================\n");
		while (p)
		{
			int		i = 0;
			while (p->cmd[i])
				dprintf(2, "p->cmd = [%s]\n", p->cmd[i++]);
			dprintf(2, "dans p:\n");
			dprintf(2, "split = [%c]\n", p->split);
			dprintf(2, "fd in = [%d] - fd out = [%d], - fd error = [%d]\n", p->fd_in, p->fd_out, p->fd_error);
			dprintf(2, "\ndans les redirections:\n");
			if (!red)
				dprintf(2, "red est NULL\n");
			else
			{
				while (red)
				{
					dprintf(2, "red fd in = [%s], red fd out = [%s], red fd = [%d], red token = [%s]\n", red->fd_in, red->fd_out, red->fd, red->token);
					red = red->next;
				}
			}
			if (p)
				p = p->next;
			red = p->redirect;
		}
		dprintf(2, "=======================================\n");
	}
}

void			get_all_redirections_done(t_process *p, t_pos *pos,
				t_redirect *red)
{
	int			is_builtin;
	int			check;
	int			i;

	i = -1;
	check = 0;
	is_builtin = test_builtin(p);
	end_pipe_redirection(pos, p, is_builtin);
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
			aggregation_redirection_behavior(red, p);
		else if (ft_strcmp(red->token, "<&") == 0 ||
				ft_strcmp(red->token, ">&") == 0)
			aggregation_file_redirection(red, p, NULL);
		red = red->next;
	}
	init_pipe_redirection(pos, p, is_builtin, check);
}
