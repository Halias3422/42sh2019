#include "../../includes/termcaps.h"

void		put_foreground(t_job *j)
{
	kill(-j->pgid, SIGCONT);
	j->status = 'r';
	tcsetpgrp(0, j->pgid);
	wait_process(j->pgid);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
}

int				rerun_job(t_job *j)
{
	put_foreground(j);
	return (0);
}

t_job		*find_job_by_id(char *argv)
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

int				ft_fg(t_process *p, t_var **var)
{
	t_job		*job;

	if (ft_tabclen(p->cmd) <= 1)
	{
		ft_printf("usage: fg %[job_id]");
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
			ft_printf("fg: job bot found");
	}
	var = NULL;
	return (1);
}
