/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:23 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:25:36 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/exec.h"

void			put_background(t_job *j)
{
	kill(-j->pgid, SIGCONT);
}

t_job			*find_plus(t_job_list *j)
{
	t_job_list		*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp->j);
		tmp = tmp->next;
	}
	return (NULL);
}

char			*find_split_process(t_process *p)
{
	if (p->split == 'A')
		return (" && ");
	else if (p->split == '|')
		return (" || ");
	else if (p->split == 'P')
		return (" | ");
	else
		return ("");
}

char			*find_all_cmd(t_job *j)
{
	int			i;
	t_process	*pt;
	char		*res;

	pt = j->p;
	res = ft_strdup("");
	while (pt)
	{
		i = -1;
		while (pt->cmd[++i])
		{
			ft_strjoin_free(&res, pt->cmd[i]);
			ft_strjoin_free(&res, " ");
		}
		if (pt->split)
			ft_strjoin_free(&res, find_split_process(pt));
		pt = pt->next;
	}
	if (j->split == '&')
		ft_strjoin_free(&res, " &");
	else
		ft_strjoin_free(&res, " ;");
	return (res);
}

int				ft_bg(t_process *p, t_var **var)
{
	t_job		*job;
	char		*tmp;

	if (ft_tabclen(p->cmd) <= 1)
		job = find_plus(stock(NULL, 10));
	else
		job = find_job_by_id(p->cmd[1]);
	if (job != NULL)
	{
		kill(-job->pgid, SIGCONT);
		job->status = 'r';
		ft_printf("[%d]%c %s\n", job->id, job->current,
		tmp = find_all_cmd(job));
		ft_strdel(&tmp);
		return (0);
	}
	else
		ft_printf_err("bg: no such job\n", p->fd_out);
	var = NULL;
	return (1);
}
