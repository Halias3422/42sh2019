/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_heredoc.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 12:48:03 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 10:55:28 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			go_next_token(t_lexeur **res, int *t)
{
	int		i;

	i = 0;
	if (res[*t] && res[*t + 1] && res[*t + 1]->token == (enum e_token)-1)
		(*t)++;
	while (res[*t] && res[*t]->word)
	{
		i++;
		(*t)++;
	}
	return (i);
}

void		fill_heredoc_init(t_lexeur **res, t_redirect *tmp, int *t)
{
	tmp->token = g_fill_token[res[*t]->token].name;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
}
