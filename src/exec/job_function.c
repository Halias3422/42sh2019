/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 12:00:18 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_job_list	*new_job(t_job *j, int number)
{
	t_job_list *job_list;

	if (!(job_list = malloc(sizeof(t_job_list))))
		return (NULL);
	j->id = number;
	job_list->j = j;
	job_list->next = NULL;
	return (job_list);
}

void		add_job(t_job *j)
{
	t_job_list	*job_list;
	t_job_list	*start;
	int			i;

	start = stock(NULL, 10);
	if (start == NULL)
		start = new_job(j, 1);
	else
	{
		i = 2;
		job_list = start;
		while (job_list->next != NULL)
		{
			i++;
			job_list = job_list->next;
		}
		job_list->next = new_job(j, i);
	}
	stock(start, 9);
}

void		remove_job(int id)
{
	t_job_list	*job_list;
	t_job_list	*start;
	t_job_list	*last;

	start = stock(NULL, 10);
	job_list = start;
	if (job_list->j->id == id)
	{
		stock(NULL, 9);
		return ;
	}
	while (job_list)
	{
		if (job_list->j->id == id)
		{
			last->next = job_list->next;
		//	free(job_list);
			break ;
		}
		last = job_list;
		job_list = job_list->next;
	}
	stock(start, 9);
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
