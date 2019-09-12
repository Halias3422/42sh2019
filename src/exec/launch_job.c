/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 16:59:05 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_process	*get_and_or(t_process *p)
{
	if (p->split != '|' && p->split != 'A')
		return (p->next);
	if (p->split == '|' && p->ret != 0)
		return (p->next);
	else if (p->split == 'A' && p->ret == 0)
		return (p->next);
	return (p->next->next);
}

int			redirect_fd(t_process *p)
{
	p->fd_out = 1;
	return (1);
}

void		alert_job(t_job *j)
{
	if (j->p->builtin != 1)
	{
		if (j->split == '&')
			print_start_process(j);
		else if (job_is_stoped(j))
			j->notified = 1;
		else
			remove_job(j->id);
	}
}

void		close_fd(t_process *p)
{
	if (p->fd_in != STDIN_FILENO)
		close(p->fd_in);
	if (p->fd_out != STDOUT_FILENO)
		close(p->fd_out);
}

void		launch_job(t_job *j, t_var *var)
{
	t_process	*p;
	int			infile;
	int			mypipe[2];

	infile = 0;
	p = j->p;
	if (j->p->builtin == 0)
		add_job(j);
	j->status = 'r';
	while (p)
	{
		p->fd_in = infile;
		if (p->split == 'P')
		{
			pipe(mypipe);
			p->fd_out = mypipe[1];
		}
		else
			redirect_fd(p);
		fork_simple(j, p, var);
		close_fd(p);
		infile = mypipe[0];
		p = get_and_or(p);
	}
	alert_job(j);
}
