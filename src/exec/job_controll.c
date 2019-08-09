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

void		print_job(t_job *j)
{
	t_process	*process;
	int			i;

	ft_printf("[%d] %d (%c) ",j->id , j->pgid, j->status);
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
	t_process *p;

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
	int		status;
	pid_t	pid_test;
	int		job_id;

	pid_test = waitpid(WAIT_ANY, &status, WUNTRACED);
	if (pid_test > 0)
	{
		if (WIFEXITED(status))
		{
			job_id = find_job_pgid(pid_test);
			set_job_status(job_id, 'd');
			//printf("%s %d %d\n", "finis", WEXITSTATUS(status), pid_test);
		}
		else if (WIFSIGNALED(status))
		{
			job_id = find_job_pgid(pid_test);
			set_job_status(job_id, 'd');
			//printf("%s %d\n", "terminated", WTERMSIG(status));
		}
		else if (WSTOPSIG(status))
		{
			job_id = find_job_pgid(pid_test);
			set_job_status(job_id, 'd');
			//printf("%s\n", "stope");
		}
	}
	else
		printf("%s\n", "ok retour a 127 ???");
	pid = 0;
}

void		put_foreground(t_job *j, int cont)
{
	if (cont)
		kill(-j->pgid, SIGCONT);
	tcsetpgrp(0, j->pgid);
	wait_process(j->pgid);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
}

void		put_background(t_job *j, int cont)
{
	if (cont)
		kill(j->pgid, SIGCONT);
}
