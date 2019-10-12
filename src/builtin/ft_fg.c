/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:48 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 16:24:26 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/builtin.h"

void			put_foreground(t_job *j, t_var **var, t_process *p)
{
	t_pos		*pos;

	pos = to_stock(NULL, 1);
	pos->last_cmd_on_bg = 1;
	kill(-j->pgid, SIGCONT);
	j->status = 'r';
	tcsetpgrp(0, j->pgid);
	wait_process(var);
	signal(SIGTTOU, SIG_IGN);
	if (p->background == 0)
		tcsetpgrp(0, getpid());
	else
		tcsetpgrp(0, p->pid);
	signal(SIGTTOU, SIG_DFL);
}

int				rerun_job(t_job *j, t_var **var, t_process *p)
{
	put_foreground(j, var, p);
	return (0);
}

void			move_plus_and_minus_indicators(t_job_list *j, t_job_list *save)
{
	t_job_list *tmp;

	tmp = save;
	ft_printf("{T.purple.}impression du fin\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.purple.}fin\n");

	if (j && j->j && j->j->current == '+' && save == j)
	{
		ft_printf("-1-\n");
		save->j->current = ' ';
		while (save->next)
			save = save->next;
		save->j->current = '-';
		save->j->was_a_plus = 1;
		if (save->next)
		{
			save->next->j->current = '+';
			save->next->j->was_a_plus = 0;
		}
		else
		{
			save->j->current = '+';
			save->j->was_a_plus = 0;
		}
	}
	else if (j && save && save->j && save->j->current == '+' && j != save)
	{
		ft_printf("-2-\n");
		save->j->was_a_plus = 0;
		return ;
	}
	else if (j && j->j && save && save->j)
	{
		ft_printf("-3-\n");
		go_through_jobs_for_current(j, save);
	}
	tmp = save;
	ft_printf("{T.purple.}impression du fin\n");
	print_all_jobs(tmp, 0);
	ft_printf("{T.purple.}fin\n");
}
/*
void			replace_was_plus_and_minus(t_job_list *head)
{
	t_job_list	*tmp;

	tmp = head;
	if (head->next == NULL && head->j->current == '+')
		head->j->was_a_plus = 0;
	else
	{
		while (head)
		{
			if (head->next->next == NULL && head->next->j->current == '+')
			{
				head->j->current = '-';
				head->j->was_a_plus = 1;
			}
			else if (head->next == NULL)
			{
				head->j->current = '-';
				head->j->was_a_plus = 1;
			}
			if (head->j->current == '+')
				head->j->was_a_plus = 0;
			head = head->next;
		}
	}
}
*/
t_job			*find_job_by_id(char *argv)
{
	int			pid;
	t_job_list	*job_list;
	char		*name;
	t_job_list	*save;

	job_list = stock(NULL, 10);
	pid = ft_atoi(argv);
	name = ft_strnew(0);
	save = job_list;
	while (job_list)
	{
		name = built_job_name(job_list, name);
		if (job_list->j->pgid == pid || job_list->j->id == pid ||
				ft_strncmp(name, argv, ft_strlen(name) == 0))
		{
			move_plus_and_minus_indicators(job_list, save);
		//	replace_was_plus_and_minus(save);
			ft_strdel(&name);
			return (job_list->j);
		}
		ft_strdel(&name);
		job_list = job_list->next;
	}
	return (NULL);
}

int				ft_fg(t_process *p, t_var **var)
{
	t_job		*job;

	if (ft_tabclen(p->cmd) <= 1)
	{
		job = find_plus(stock(NULL, 10));
		move_plus_and_minus_indicators(find_plus_jb(stock(NULL, 10)),
			stock(NULL, 10));
		if (job != NULL)
			return (rerun_job(job, var, p));
		else
			ft_printf_err("bg: current: no such job\n", p->fd_out);
	}
	else
	{
		job = find_job_by_id(p->cmd[1]);
		if (job != NULL)
			return (rerun_job(job, var, p));
		else
			ft_putstr_fd("fg: job not found", p->fd_out);
	}
	return (1);
}
