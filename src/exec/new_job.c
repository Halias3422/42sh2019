/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 07:30:17 by mjalenqu    ###    #+. /#+    ###.fr     */
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
	job_list->j->current = '+';
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
			job_list->j->current = ' ';
			job_list = job_list->next;
		}
		job_list->next = new_job(j, i);
		job_list->j->current = '-';
	}
	stock(start, 9);
}
