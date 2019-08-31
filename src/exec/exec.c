/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/31 17:30:58 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

void		init_job(t_job *j)
{
	j->split = '\0';
	j->status = '\0';
}

void		fill_job(t_job *j, t_lexeur **res)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (res[i])
	{
		if (res[i]->token == 1 || res[i]->token == 8)
		{
			if (res[i]->token == 1)
				j->split = '&';
			else
				j->split = ';';
			if (res[i + 1])
			{
				j->next = malloc(sizeof(t_job));
				j = j->next;
				init_job(j);
			}
		}
		if (res[i])
			i++;
	}
	j->next = NULL;
}

void		print_exec(t_job *j)
{
	int		i = 0;
	t_job		*s_j;
	t_process	*s_p;

	while (j)
	{
		s_j = j;
		while (j->p)
		{
			s_p = j->p;
			while (j->p->cmd[i])
			{
		//		printf("cmd[%d] _%s_\n", i, j->p->cmd[i]);
				i++;
			}
		//	printf("token_%s_\tfile_out_%s_\n", j->p->token, j->p->file_out);
			j->p = j->p->next;
		}
		i = 0;
		j->p = s_p;
		j = j->next;
	}
	j = s_j;
}

int			start_exec(t_lexeur **res, t_var *var)
{
	t_job		*j;

	j = malloc(sizeof(t_job));
	j->pgid = 0;
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);
	print_exec(j);
	while (j)
	{
		launch_job(j, var);
		j = j->next;
	}
	//main_exec(j, var);
	return (0);
}
