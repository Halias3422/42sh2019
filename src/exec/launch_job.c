/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/29 18:52:02 by husahuc     ###    #+. /#+    ###.fr     */
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
	/*p->file_out = p->cmd[1];
	p->file_in = p->cmd[1];
	p->split = 0;
	if (p->split == 'f')
		p->fd_out = open(p->file_out, O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (p->split == 'F')
		p->fd_out = open(p->file_out, O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (p->split == '<')
		p->fd_in = open(p->file_in, O_RDONLY);
	else
		p->fd_out = 1;
	if (p->fd_in < 0)
	{
		ft_printf_err("42sh: %s: No such file or directory", p->file_in);
		return (-1);
	}
	else if (p->fd_out < 0)
	{
		ft_printf_err("42sh: %s: No such file or directory", p->file_out);
		return (-1);
	}*/
	//launch_redirection(p);
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
