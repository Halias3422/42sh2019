/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 10:58:58 by vde-sain    ###    #+. /#+    ###.fr     */
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

int			start_exec(t_lexeur **res, t_var *var)
{
	t_job		*j;

	j = malloc(sizeof(t_job));
	j->pgid = 0;
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);

	while (j)
	{
		launch_job(j, var);
		j = j->next;
	}
	return (0);
}
