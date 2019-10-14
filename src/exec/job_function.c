/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 11:14:05 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

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

void		remove_plus(t_job_list *tmp)
{
	while (tmp)
	{
		if (tmp->j->current == '+')
			tmp->j->current = ' ';
		tmp = tmp->next;
	}
}

int			place_minus_before_plus(t_job_list *save)
{
	t_job_list	*tmp;
	int			check;

	check = 0;
	tmp = save;
	while (tmp)
	{
		if (tmp->j->current == '-')
			check = 1;
		tmp = tmp->next;
	}
	if (save && check == 0 && save->j->current == '+')
	{
		if (save->next == NULL)
			return (1);
		while (save->next)
			save = save->next;
		save->j->current = '-';
		save->j->was_a_plus = 1;
		return (1);
	}
	else if (check == 0)
	{
		while (check != 1 && save)
		{
			if (save->next && save->next->j->current == '+')
			{
				save->j->current = '-';
				save->j->was_a_plus = 1;
			}
			save = save->next;
		}
		return (1);
	}
	return (0);
}

void		replace_plus_and_minus(t_job_list *start)
{
	int			check;
	t_job_list	*tmp;

	check = 0;
	tmp = start;

	ft_printf("{T.green.}impression du debut 1\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.green.}fin\n");

	check = place_minus_before_plus(start);

/*	ft_printf("{T.green.}impression du debut\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.green.}fin\n");

	while (start)
	{
		if (start->j->was_a_plus == 1)
			check += 1;
		start = start->next;
	}
*/	start = tmp;

	ft_printf("{T.green.}impression du milieu\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.green.}fin  check = %d\n", check);

	while (start && check == 0)
	{
		if (start->j->current == '-')
			start->j->current = '+';
		if (start->j->was_a_plus == 1)
			start->j->current = '-';
		start = start->next;
	}
	ft_printf("{T.green.}impression du milieu\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.green.}fin  check = %d\n", check);

//	if (tmp && check == 0)
//		place_minus_before_plus(tmp);

	ft_printf("{T.green.}impression du fin\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.green.}fin\n");

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

	ft_printf("{T.yellow.}impression du debut\n");
	print_all_jobs(start, 0);
	ft_printf("{T.yellow.}fin\n");

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

	replace_plus_and_minus(start);

	ft_printf("{T.yellow.}impression des jobs fin\n");
	print_all_jobs(start, 0);
	ft_printf("{T.yellow.}fin\n");
	
	check_if_jobs_are_empty(start);
	ft_printf("{T.yellow.}impression des jobs fin\n");
	print_all_jobs(start, 0);
	ft_printf("{T.yellow.}fin\n");


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
