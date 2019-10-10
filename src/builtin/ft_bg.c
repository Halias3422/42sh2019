/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:23 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 16:56:53 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/exec.h"

void			put_background(t_job *j)
{
	kill(-j->pgid, SIGCONT);
}

t_job		*find_plus(t_job_list *j)
{
	t_job_list		*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp->j);
		tmp = tmp->next;
	}
	return (NULL);
}

int				ft_bg(t_process *p, t_var **var)
{
	t_job		*job;

	if (ft_tabclen(p->cmd) <= 1)
	{
		job = find_plus(stock(NULL, 10));
		if (job)
		{
			put_background(job);
			print_job(job);
		}
		else
			ft_printf_err("bg: current: no such job\n");
		return (1);
	}
	else
		job = find_job_by_id(p->cmd[1]);
	if (job != NULL)
	{
		kill(-job->pgid, SIGCONT);
		job->status = 'r';
		print_job(job);
		return (0);
	}
	else
		ft_putstr_fd("bg: job not found\n", p->fd_out);
	var = NULL;
	return (1);
}
