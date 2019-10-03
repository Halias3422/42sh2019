/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_controll.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <husahuc@student.42.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 17:35:39 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		free_redirections(t_redirect *ptr_redi)
{
	t_redirect *r;
	t_redirect *next;

	r = ptr_redi;
	while (r)
	{
		if (r->fd_out)
			free(r->fd_out);
		if (r->fd_in)
			free(r->fd_in);
		if (r->token)
			free(r->token);
		next = r->next;
		free(r);
		r = next;
	}
}

void		free_process(t_process *ptr_p)
{
	t_process *p;
	t_process *next;

	p = ptr_p;
	while (p)
	{
		ft_tabfree(p->cmd);
		free_redirections(p->redirect);
		next = p->next;
		free(p);
		p = next;
	}
}

void		free_job(t_job *j)
{
	free_process(j->p);
	free(j);
}
