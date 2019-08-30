/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_controll.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <husahuc@student.42.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 16:38:33 by husahuc     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void		process_status(t_process *process, t_job_list *job_list, int status)
{
	if (WIFSTOPPED(status))
	{
		job_list->j->status = 's';
		process->stoped = STOPED;
		job_list->j->notified = 1;
		print_job(job_list->j);
	}
	else
	{
		if (WIFSIGNALED(status))
			ft_printf_err("terminated by signal %d", WTERMSIG(status));
		job_list->j->status = 'f';
		process->completed = FINISHED;
		if (!process->builtin)
			process->ret = WEXITSTATUS(status);
	}
}

int			mark_process_status(pid_t pid, int status)
{
	t_job_list	*job_list;
	t_process	*process;

	job_list = stock(NULL, 10);
	if (pid > 0)
	{
		while (job_list)
		{
			process = job_list->j->p;
			while (process)
			{
				if (process->pid == pid)
				{
					process->status = status;
					process_status(process, job_list, status);
					return (0);
				}
				process = process->next;
			}
			job_list = job_list->next;
		}
	}
	return (-1);
}

void		print_job(t_job *j)
{
	t_process	*process;
	int			i;

	ft_printf("[%d] %d	", j->id, j->pgid);
	if (j->status == 'f')
		ft_printf("Done	");
	else if (j->status == 's')
		ft_printf("Stopped	");
	else
		ft_printf("running	");
	process = j->p;
	while (process)
	{
		i = -1;
		while (process->cmd[++i])
		{
			ft_printf("%s ", process->cmd[i]);
		}
		process = process->next;
	}
	ft_putchar('\n');
}

void		print_start_process(t_job *j)
{
	t_process	*p;

	p = j->p;
	ft_printf("[%d]", j->id);
	while (p)
	{
		ft_printf(" %d", p->pid);
		p = p->next;
	}
	ft_putchar('\n');
}

void		wait_process(pid_t pid)
{
	int			status;
	pid_t		pid_test;

	pid = 0;
	pid_test = waitpid(WAIT_ANY, &status, WUNTRACED);
	mark_process_status(pid_test, status);
}
