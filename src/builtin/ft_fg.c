#include "../../includes/termcaps.h"

int				rerun_job(t_job *j)
{
	kill(-j->pgid, SIGCONT);
	tcsetpgrp(0, j->pgid);
	j->status = '\0';
	wait_process(j->pgid);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
	return (0);
}

int				ft_fg(t_process *p, t_var **var)
{
	pid_t		pid;
	t_job_list	*job_list;

	pid = ft_atoi(p->cmd[1]);
	job_list = stock(NULL, 10);
	while (job_list)
	{
		if (job_list->j->pgid == pid)
			rerun_job(job_list->j);
		job_list = job_list->next;
	}
	var = NULL;
	return (0);
}
