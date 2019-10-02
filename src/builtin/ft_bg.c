/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:23 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 11:03:43 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/exec.h"

void		put_background(t_job *j)
{
	kill(-j->pgid, SIGCONT);
}

int			ft_bg(t_process *p, t_var **var)
{
	t_job		*job;

	if (ft_tabclen(p->cmd) <= 1)
	{
		ft_putstr_fd("usage: bg %[job_id]", p->fd_out);
		return (1);
	}
	else
	{
		job = find_job_by_id(p->cmd[1]);
		if (job != NULL)
		{
			kill(-job->pgid, SIGCONT);
			job->status = 'r';
			print_job(job);
			return (0);
		}
		else
			ft_putstr_fd("bg: job bot found", p->fd_out);
	}
	var = NULL;
	return (1);
}
