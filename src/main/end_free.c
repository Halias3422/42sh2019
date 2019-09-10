#include "../../includes/exec.h"

void		free_job_list(t_job_list *job_list)
{
	free(job_list);
}

void		free_all_job_list(void)
{
	t_job_list	*job_list;
	t_job_list	*next;

	job_list = stock(NULL, 10);
	if (job_list == NULL)
		return ;
	while (job_list)
	{
		next = job_list->next;
		free_job_list(job_list);
		job_list = next;
	}
	stock(NULL, 9);
}

void		end_free(void)
{
	free_all_job_list();
}
