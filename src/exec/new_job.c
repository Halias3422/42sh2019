/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 14:33:10 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_save_job		*add_list_save_job(t_job *save, t_save_job *chain)
{
	t_save_job	*new;

	new = NULL;
	if (!(new = (t_save_job*)malloc(sizeof(t_save_job))))
		return (NULL);
	if (chain == NULL)
	{
		new->current = save->current;
		new->was_a_plus = save->was_a_plus;
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	while (chain->next != NULL)
		chain = chain->next;
	new->current = save->current;
	new->was_a_plus = save->was_a_plus;
	new->next = NULL;
	new->prev = chain;
	chain->next = new;
	return (new);
}

t_save_job		*copy_job_list(t_job_list *save)
{
	t_save_job	*chain;
	t_save_job	*head;

	chain = NULL;
	while (save)
	{
		if (chain == NULL)
		{
			head = add_list_save_job(save->j, chain);
			chain = head;
		}
		else
			chain = add_list_save_job(save->j, chain);
		save = save->next;
	}
	return (head);
}

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

void		free_copy_job(t_save_job *copy)
{
	t_save_job	*tmp;

	tmp = NULL;
	while (copy)
	{
		tmp = copy;
		copy = copy->next;
		free(tmp);
	}
	to_stock(NULL, 2);
}

static void		print_save_job(t_save_job *chain)
{
	while (chain)
	{
		ft_printf("current = %c ", chain->current);
		ft_printf("was_a_plus = %d\n", chain->was_a_plus);
		chain = chain->next;
	}
}


void		add_job(t_job *j)
{
	t_job_list	*job_list;
	t_job_list	*start;
	t_save_job	*copy;
	int			i;

	t_save_job	*test;

	test = to_stock(NULL, 3);
	copy = NULL;
	start = stock(NULL, 10);

	free_copy_job(test);
	test = NULL;

	copy = copy_job_list(start);
	if (DEBUG)
	{
	ft_printf("{T.red.}avant boucle de creation copy = \n");
	print_save_job(copy);
	ft_printf("{T.red.}fin\n");
	}
	to_stock(copy, 2);
	
	if (start == NULL)
	{
		start = new_job(j, 1);
		start->j->current = '+';
		if (DEBUG)
		{
		ft_printf("{T.red.B.}apres boucle de creation\n");
		print_all_jobs(start, 0);
		ft_printf("{T.red.B.}fin\n");
		}
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
		if (DEBUG)
		{
		ft_printf("{T.red.B.}apres boucle de creation\n");
		print_all_jobs(start, 0);
		ft_printf("{T.red.B.}fin\n");
		}
	}
	stock(start, 9);

}
