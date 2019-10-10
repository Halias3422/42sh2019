/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 10:48:19 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void		remove_job(int id)
{
	t_job_list	*job_list;
	t_job_list	*start;
	t_job_list	*last;

	start = stock(NULL, 10);
	job_list = start;
	if (job_list->j->id == id)
	{
		free_job(job_list->j);
		free(job_list);
		stock(NULL, 9);
		return ;
	}
	while (job_list)
	{
		if (job_list->j->id == id)
		{
			last->next = job_list->next;
			free(job_list);
			break ;
		}
		last = job_list;
		job_list = job_list->next;
	}
	stock(start, 9);
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
			ft_printf("%s ", process->cmd[i]);
		process = process->next;
	}
	ft_putchar('\n');
}

int			find_job_pgid(pid_t pgid)
{
	t_job_list	*job_list;

	job_list = stock(NULL, 10);
	if (job_list == NULL)
		return (-1);
	while (job_list)
	{
		if (job_list->j->pgid == pgid)
			return (job_list->j->id);
		job_list = job_list->next;
	}
	return (-1);
}
