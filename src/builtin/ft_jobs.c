/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:34 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 10:49:39 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/termcaps.h"

void			print_status_job(char status)
{
	if (status == 'f')
		ft_printf("Done	");
	else if (status == 's')
		ft_printf("Stopped	");
	else
		ft_printf("running	");
}

void			print_ft_job(t_job *j, int option)
{
	t_process	*process;
	int			i;

	if (option == 1)
		ft_printf("[%d] %c %d	", j->id, j->current, j->pgid);
	else if (option == 2)
	{
		ft_printf("%d\n", j->pgid);
		return ;
	}
	else
		ft_printf("[%d] %c	", j->id, j->current);
	print_status_job(j->status);
	process = j->p;
	while (process)
	{
		i = -1;
		while (process->cmd[++i])
		{
			ft_printf("%s ", process->cmd[i]);
		}
		process = process->next;
	}
	ft_putchar('\n');
	option = 0;
}

int				ft_jobs_option(char **cmd)
{
	if (ft_tabclen(cmd) > 1)
	{
		if (cmd[1][0] == '-')
		{
			if (cmd[1][1] == 'l')
				return (1);
			else if (cmd[1][1] == 'p')
				return (2);
		}
		else
			return (-1);
	}
	return (0);
}

int				ft_jobs(t_process *p, t_var **var)
{
	t_job_list	*job_list;
	int			option;

	option = ft_jobs_option(p->cmd);
	job_list = stock(NULL, 10);
	while (job_list != NULL)
	{
		print_ft_job(job_list->j, option);
		job_list = job_list->next;
	}
	p = NULL;
	var = NULL;
	return (0);
}
