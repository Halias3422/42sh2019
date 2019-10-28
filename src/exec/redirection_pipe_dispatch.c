/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 17:29:03 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <fcntl.h>

static void		init_pipe_redirection(t_pos *pos, t_process *p, int is_builtin)
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

static void		end_pipe_redirection(t_pos *pos, t_process *p, int is_builtin,
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

void			get_all_redirections_done(t_process *p, t_pos *pos,
				t_redirect *red)
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
			aggregation_redirection_behavior(red, p);
		else if (ft_strcmp(red->token, "<&") == 0 ||
				ft_strcmp(red->token, ">&") == 0)
			aggregation_file_redirection(red, p);
		red = red->next;
	}
	end_pipe_redirection(pos, p, is_builtin, check);
}
