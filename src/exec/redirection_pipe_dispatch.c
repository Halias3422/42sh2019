/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 19:37:46 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int				is_all_num(char *str)
{
	int			i;

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
/*
static void		end_pipe_redirection(t_pos *pos, t_process *p, int is_builtin)
{
	(void)is_builtin;
	if (pos->pipe > 0)
	{
		pos->act_fd_out = 1;
		if (is_builtin != 1)
		{
			close(pos->pipe);
			if (!p->redirect)
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
		{
			pos->act_fd_out = ft_atoi(p->redirect->fd_out);
		}
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

void			get_all_redirections_done(t_process *p, t_pos *pos,
				t_redirect *red, int is_builtin)
{
	int			check;
	int			i;

	i = -1;
	check = 0;
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
		if (p->fd_in == 0 && ft_strcmp(p->redirect->token, "<") == 0)
		{
			if (p->split == 'P' && is_builtin == 1 && p->redirect && ft_strcmp(p->redirect->token, "<") == 0)
			{
				ft_strdel(&p->redirect->fd_in);
				p->redirect->fd_in = ft_strdup("1");
				ft_strdel(&p->redirect->fd_out);
				p->redirect->fd_out = ft_strdup("1");
			}
			p->fd_in = 1;
		}
	}
	init_pipe_redirection(pos, p, is_builtin, check);
}
*/
