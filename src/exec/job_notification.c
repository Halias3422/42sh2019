/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_notification.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:45 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 16:26:00 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status, stock(NULL, 6)))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	}
}

int			job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->p;
	while (p)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int			job_is_stoped(t_job *j)
{
	t_process	*p;

	p = j->p;
	while (p)
	{
		if (p->stoped == 0)
		{
			return (0);
		}
		p = p->next;
	}
	return (1);
}

void		free_job(t_job_list *j)
{
	free(j);
}

void		job_notification(void)
{
	t_job_list	*job_list;
	t_job_list	*last;
	t_job_list	*first_job;
	t_job_list	*next;

	last = NULL;
	update_status();
	first_job = stock(NULL, 10);
	job_list = first_job;
	while (job_list)
	{
		next = job_list->next;
		if (job_is_completed(job_list->j))
		{
			print_job(job_list->j);
			if (last)
				last->next = next;
			else
				first_job = next;
			free_job(job_list);
		}
		else if (job_is_stoped(job_list->j) && !job_list->j->notified)
		{
			job_list->j->notified = 1;
			print_job(job_list->j);
			last = job_list;
		}
		else
			last = job_list;
		job_list = next;
	}
	stock(first_job, 9);
}
