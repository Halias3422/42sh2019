/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/25 10:13:42 by mjalenqu    ###    #+. /#+    ###.fr     */
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

void		alert_job(t_job *j)
{
	if (j->p->builtin == 1 && j->split != '&')
		return ;
	if (j->split == '&')
		print_start_process(j);
	else if (job_is_stoped(j))
		j->notified = 1;
	else
		remove_job(j->id);
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

	infile = 0;
	p = j->p;
	if (j->p->builtin == 0 || j->split == '&')
		add_job(j);
	j->status = 'r';
	before_redirection(p);
	while (p)
	{
		if (p->cmd[0] && find_equal(p->cmd[0]) == 1)
			if ((p->cmd = check_exec_var(p->cmd, &var)) == NULL)
				return ;
		fork_simple(j, p, &var);
		close_fd(p);
		p = get_and_or(p);
		free_temp(&var);
	}
	alert_job(j);
}
