/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 18:26:30 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		normal_redirection_behavior(t_redirect *red, t_process *p)
{
	int	new_fd_out;
	t_pos	*pos;
	int		init_fd;
	char	*file;


	file = ft_strdup("./");
	file = ft_strjoinf(file, red->fd_out, 1);
	new_fd_out = 1;
	init_fd = red->fd;
	pos = to_stock(NULL, 1);
	if (access(red->fd_out, F_OK) != -1 && access(red->fd_out, X_OK) != -1)
	{
		if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, "<") == 0)
		new_fd_out = open(file, O_RDWR | O_TRUNC);
		else if (ft_strcmp(red->token, ">>") == 0)
			new_fd_out = open(file, O_RDWR | O_APPEND);
	}
	else if (access(red->fd_out, F_OK) != -1 && access(red->fd_out, W_OK) == -1)
		ft_printf("42sh: %s: permission denied\n", red->fd_out);
	else
		new_fd_out = open(file, O_RDWR | O_CREAT, 0666);
	if (ft_strcmp(red->token, "<<") == 0)
		dup2(red->fd, 1);
	else if (test_builtin(p) != 1)
		dup2(red->fd, new_fd_out);
	if (init_fd == 1)
		pos->act_fd_out = new_fd_out;
	if (init_fd == 2)
		pos->act_fd_error = red->fd;
	to_stock(pos, 0);
}

void		get_all_redirections_done(t_process *p)
{
	t_redirect	*red;

	red = p->redirect;
	if (red && red->token)
	while (red)
	{
		if (ft_strcmp(red->token, "<") == 0 || ft_strcmp(red->token, "<<") == 0
		|| ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">>") == 0)
			normal_redirection_behavior(red, p);
		red = red->next;
	}
}
