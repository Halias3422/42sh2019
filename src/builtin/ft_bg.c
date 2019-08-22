#include "../../includes/termcaps.h"
#include "../../includes/exec.h"

void		put_background(t_job *j)
{
	kill(-j->pgid, SIGCONT);
}

int			ft_bg(t_process *p, t_var **var)
{
	t_job		*job;

	if (ft_tabclen(p->cmd) <= 1)
	{
		ft_printf("usage: bg %[job_id]");
		return (1);
	}
	else
	{
		job = find_job_by_id(p->cmd[1]);
		if (job != NULL)
		{
			kill(-job->pgid, SIGCONT);
			job->status = 'r';
			print_job(job);
			return (0);
		}
		else
			ft_printf("bg: job bot found");
	}
	var = NULL;
	return (1);
}
