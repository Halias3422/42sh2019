/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fg_bg_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 16:07:08 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 16:13:56 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_job_list		*find_plus_jb(t_job_list *j)
{
	t_job_list	*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_job			*find_plus(t_job_list *j)
{
	t_job_list	*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp->j);
		tmp = tmp->next;
	}
	return (NULL);
}

void			go_through_jobs_for_current(t_job_list *j, t_job_list *save)
{
	j->j->current = ' ';
	while (save->next)
	{
		if (save->next->j->current == '-')
		{
			save->next->j->current = '+';
			save->j->current = '-';
		}
		save = save->next;
	}
}

void			change_plus_and_minus_indicators(t_job_list *jb, t_job *j,
				t_job_list *save)
{
	if (jb->j == j)
		return ;
	while (save)
	{
		if (save->j->current == '-')
			save->j->current = ' ';
		save = save->next;
	}
	if (j)
		j->current = '-';
	jb->j->current = '+';
}
