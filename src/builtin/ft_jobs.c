#include "../../includes/builtin.h"
#include "../../includes/termcaps.h"

int				ft_jobs(t_process *p, t_var **var)
{
	t_job_list *job_list;

	job_list = stock(NULL, 10);
	while (job_list != NULL)
	{
		print_job(job_list->j);
		job_list = job_list->next;
	}
	p = NULL;
	var = NULL;
	return (0);
}
