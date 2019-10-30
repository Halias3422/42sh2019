/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 15:13:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 16:12:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		normal_redirection_behavior(t_redirect *red)
{
	ft_printf("STDIN = %d\n", STDIN_FILENO);
	if (ft_strcmp(red->token, "<<") == 0)
		dup2(red->fd, STDIN_FILENO);
	ft_printf("APRES STDIN = %d\n", STDIN_FILENO);
}

void		get_all_redirections_done(t_process *p)
{
	t_redirect	*red;

	ft_printf("je viens la\n");
	red = p->redirect;
	while (red)
	{
		if (ft_strcmp(red->token, "<") == 0 || ft_strcmp(red->token, "<<") == 0
		|| ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">>") == 0)
			normal_redirection_behavior(red);
		red = red->next;
	}
}
