/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 13:49:48 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_process	*get_and_or(t_process *p)
{
	if (p->split != '|' && p->split != 'A')
		return (p->next);
	if (p->split == '|' && p->ret != 0)
		return (p->next);
	else if (p->split == 'A' && p->ret == 0)
		return (p->next);
	return (p->next->next);
}

void		alert_job(t_job *j)
{
	if (j->p->builtin == 1 && j->split != '&' && is_builtin_modify(j->p))
	{
		free_job(j);
		return ;
	}
	if (j->split == '&')
		print_start_process(j);
	else if (job_is_stoped(j))
		j->notified = 1;
	else
		remove_job(j->id);
}

void		print_tab(char **cmd, int c)
{
	int i =0;

	if (c == 1)
		ft_printf("{T.red.}------------------------------------\n");
	if (c == 2)
		ft_printf("{T.blue.}------------------------------------\n");
	if (c == 3)
		ft_printf("{T.yellow.}------------------------------------\n");
	while (cmd[i])
	{
		ft_printf("tab[%d]=%s\n", i, cmd[i]);
		i++;
	}
	ft_printf("{eoc}");
}

void		launch_job(t_job *j, t_var *var)
{
	t_process	*p;
	int			infile;
	int			mypipe[2];

	p = j->p;
	if (!(j->split != '&' && is_builtin_modify(p)))
		add_job(j);
	j->status = 'r';
	before_redirection(p);
	infile = 0;
	while (p)
	{
		if (p->cmd && p->cmd[0] && find_equal(p->cmd[0]) == 1)
			if ((p->cmd = check_exec_var(p->cmd, &var)) == NULL)
				return ;
		p->fd_in = infile;
		if (p->split == 'P')
		{
			pipe(mypipe);
			p->fd_out = mypipe[1];
			fork_simple(j, p, &var);
			close(mypipe[1]);
			infile = mypipe[0];
		}
		else
		{
			p->fd_out = 1;
			fork_simple(j, p, &var);
			//infile = 0;
		}
		//fork_simple(j, p, &var);
		p = get_and_or(p);
		free_temp(&var);
	}
	alert_job(j);
}
