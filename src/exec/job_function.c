/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 07:45:19 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

static void	update_current(void)
{
	t_job_list	*job_list;
	t_job_list	*last;
	t_job_list	*penultimate;

	job_list = stock(NULL, 10);
	last = NULL;
	while (job_list)
	{
		penultimate->j->current = ' ';
		last->j->current = '-';
		job_list->j->current = '+';
		penultimate = last;
		last = job_list;
		job_list = job_list->next;
	}
}

void		remove_job_free(t_job_list **job_list, t_job_list **last,
			t_job_list **start)
{
	t_job_list *next;

	next = (*job_list)->next;
	if (*last == NULL)
		*start = next;
	else
		(*last)->next = next;
	free_job((*job_list)->j);
	free(*job_list);
	*job_list = next;
}

void		remove_job(int id)
{
	t_job_list	*job_list;
	t_job_list	*start;
	t_job_list	*last;
	int			i;

	start = stock(NULL, 10);
	job_list = start;
	i = 1;
	last = NULL;
	while (job_list)
	{
		if (job_list->j->id == id)
			remove_job_free(&job_list, &last, &start);
		else
		{
			job_list->j->id = i;
			last = job_list;
			job_list = job_list->next;
			i++;
		}
	}
	update_current();
	stock(start, 9);
}

void		print_job(t_job *j)
{
	t_process	*process;
	int			i;

	ft_printf("[%d] %c %d	", j->id, j->current, j->pgid);
	if (j->status == 'f')
		ft_printf("Done	");
	else if (j->status == 's')
		ft_printf("Stopped	");
	else
		ft_printf("Running	");
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
