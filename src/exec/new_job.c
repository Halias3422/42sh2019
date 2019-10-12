/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 15:04:02 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_job_list	*new_job(t_job *j, int number)
{
	t_job_list	*job_list;

	if (!(job_list = malloc(sizeof(t_job_list))))
		return (NULL);
	j->id = number;
	job_list->j = j;
	job_list->j->current = ' ';
	job_list->next = NULL;
	return (job_list);
}

void		place_plus_and_minus(t_job_list *head, char split)
{
	int		check;
	t_job_list	*tmp;

	check = 0;
	tmp = head;
	
//	ft_printf("--------------------------------\n");
//	ft_printf("{T.blue.B.}impression du debut\n");
//	print_all_jobs(head, 0);
//	ft_printf("{T.blue.B.}fin\n");
	
	while (head)
	{
		if (head->j->current == '+')
		{
			head->j->current = '-';
			check += 1;
		}
		else if (head->j->current == '-')
			head->j->current = ' ';
		head = head->next;
	}
	head = tmp;
	
//	ft_printf("{T.blue.B.}impression du milieu\n");
//	print_all_jobs(head, 0);
//	ft_printf("{T.blue.B.}fin\n");
	if (check == 0)
	{
		while (head)
		{
			if (head->next && head->next->next == NULL)
			{
				head->next->j->current = '+';
				head->j->current = '-';
			}
			else if (head->next == NULL && head == tmp)
				head->j->current = '+';
			head = head->next;
		}
	}
	head = tmp;
	
//	ft_printf("{T.blue.B.}impression du milieu 2\n");
//	print_all_jobs(head, 0);
//	ft_printf("{T.blue.B.}fin\n");
	
	head = tmp;
	while (head && split == '&')
	{
		head->j->was_a_plus = 0;
		head = head->next;
	}
	head = tmp;
	while (head && split == '&')
	{
		if (head->j->current == '-')
			head->j->was_a_plus = 1;
		head = head->next;
	}

//	ft_printf("{T.blue.B.}impression du fin\n");
//	print_all_jobs(head, 0);
//	ft_printf("{T.blue.B.}fin\n");
//	ft_printf("--------------------------------\n");
}

void		add_job(t_job *j)
{
	t_job_list	*job_list;
	t_job_list	*start;
	int			i;

	start = stock(NULL, 10);
	if (start == NULL)
	{
		start = new_job(j, 1);
		start->j->current = '+';

//		ft_printf("{T.red.B.}apres boucle de creation\n");
//		print_all_jobs(start, 0);
//		ft_printf("{T.red.B.}fin\n");

	}
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
		place_plus_and_minus(start, job_list->next->j->split);
		job_list->next->j->current = '+';

//		ft_printf("{T.red.B.}apres boucle de creation\n");
//		print_all_jobs(start, 0);
//		ft_printf("{T.red.B.}fin\n");

	}
	stock(start, 9);
}
