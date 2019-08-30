/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/30 16:08:36 by mdelarbr    ###    #+. /#+    ###.fr     */
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

void		print_res(t_lexeur **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		//printf("res[%d]:word -> _%s_\ttoken -> %d\tred -> _%s_\n", i, res[i]->word, res[i]->token, res[i]->redirection);
		i++;
	}
}

int			start_exec(t_lexeur **res, t_var *var)
{
	t_job		*j;

	j = malloc(sizeof(t_job));
	j->pgid = 0;
	print_res(res);
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);

	while (j)
	{
		launch_job(j, var);
		j = j->next;
	}
	//main_exec(j, var);
	return (0);
}
