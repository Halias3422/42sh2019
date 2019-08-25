/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:34 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 16:44:36 by husahuc     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
