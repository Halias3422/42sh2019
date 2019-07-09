/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_jobs.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/09 07:10:09 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/09 07:27:36 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_cmd(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		ft_strdel(&cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_all_job(t_job *j)
{
	t_process	*p_tmp;
	t_job		*j_tmp;

	while (j)
	{
		while (j->p)
		{
			free_cmd(j->p->cmd);
			ft_strdel(&j->p->token);
			ft_strdel(&j->p->redirection);
			p_tmp = j->p;
			j->p = j->p->next;
			free(p_tmp);
		}
		j_tmp = j;
		j = j->next;
		free(j_tmp);
	}
}
