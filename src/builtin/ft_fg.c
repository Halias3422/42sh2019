/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:48 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 16:54:24 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void	put_foreground(t_job *j)
{
	kill(-j->pgid, SIGCONT);
	j->status = 'r';
	tcsetpgrp(0, j->pgid);
	wait_process(stock(NULL, 6));
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
}

int		rerun_job(t_job *j)
{
	put_foreground(j);
	return (0);
}

t_job	*find_job_by_id(char *argv)
{
	int			pid;
	t_job_list	*job_list;

	job_list = stock(NULL, 10);
	pid = ft_atoi(argv);
	while (job_list)
	{
		if (job_list->j->pgid == pid || job_list->j->id == pid)
			return (job_list->j);
		job_list = job_list->next;
	}
	return (NULL);
}

int		ft_fg(t_process *p, t_var **var)
{
	t_job		*job;

	stock(*var, 5);
	if (ft_tabclen(p->cmd) <= 1)
	{
		ft_putstr_fd("usage: fg %[job_id]", p->fd_out);
		return (1);
	}
	else
	{
		job = find_job_by_id(p->cmd[1]);
		if (job != NULL)
		{
			rerun_job(job);
			return (0);
		}
		else
			ft_putstr_fd("fg: job bot found", p->fd_out);
	}
	return (1);
}
