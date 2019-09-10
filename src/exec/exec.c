/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 15:14:25 by mdelarbr    ###    #+. /#+    ###.fr     */
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
		if (res[i]->token == 1 || res[i]->token == 10)
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
	t_job			*sj;
	t_process		*sp;
	int			i;

	sj = j;
	while (j)
	{
		sp = j->p;
		while (j->p)
		{
			i = 0;
			while (j->p->cmd[i])
			{
				printf("cmd[%d]: _%s_\n", i, j->p->cmd[i]);
				i++;
			}
			printf("split _%c_\t", j->p->split);
			printf("file_out: _%s_\tfile_in: _%s_\t", j->p->file_out, j->p->file_in);
			printf("token: _%s_\n", j->p->token);
			if (j->p->redirect)
			{
				while (j->p->redirect)
				{
					printf("redirect fd_in : _%s_\tfd_out : _%s_\n", j->p->redirect->fd_in, j->p->redirect->fd_out);
					j->p->redirect = j->p->redirect->next;
				}
			}
			j->p = j->p->next;
		}
		j->p = sp;
		j = j->next;
	}
	j = sj;
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
	return (0);
}
