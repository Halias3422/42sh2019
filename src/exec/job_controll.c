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

void		print_start_process(t_job *j)
{
	t_process *p;

	p = j->p;
	while (p)
	{
		ft_printf(" %d", p->pid);
		p = p->next;
	}
	ft_putchar('\n');
}

void		check_zombie()
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	if (pid > 0)
	{
		if (WIFEXITED(status))
		{
			printf("%s %d\n", "finis", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("%s %d\n", "terminated", WTERMSIG(status));
		}
		else if (WSTOPSIG(status))
		{
			printf("%s\n", "stope");
		}
	}
}

void		wait_process(pid_t pid)
{
	int status;

	waitpid(WAIT_ANY, &status, WUNTRACED);
	//waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		printf("%s %d\n", "finis", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("%s %d\n", "terminated", WTERMSIG(status));
	}
	else if (WSTOPSIG(status))
	{
		printf("%s\n", "stope");
	}
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
	//kill(j->pgid, SIGSTOP);
	//printf("%d\n", j->pgid);
	//kill(j->pgid, SIGSTOP);
}
