/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:23 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 15:30:03 by mjalenqu    ###    #+. /#+    ###.fr     */
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

t_job_list		*find_plus_jb(t_job_list *j)
{
	t_job_list		*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp);
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
	j->current = '-';
	jb->j->current = '+';
}

static void		iterate_through_list(t_job_list *jb, char *ans)
{
	char		*name;
	t_job_list	*save;

	save = jb;
	name = ft_strnew(0);
	while (jb)
	{
		name = built_job_name(jb, name);
		if (jb->j->id == ft_atoi(ans) ||
		ft_strncmp(name, ans, ft_strlen(name)) == 0)
		{
			change_plus_and_minus_indicators(jb, find_plus(save), save);
			ft_strdel(&name);
			return ;
		}
		ft_strdel(&name);
		jb = jb->next;
	}
	ft_printf_err("42sh: bg: %s: no such job\n", ans);
}

t_job			*find_job_by_id_bg(char **cmd, int i)
{
	t_job		*j;
	t_job_list	*jb;

	jb = stock(NULL, 10);
	j = find_plus(jb);
	if (cmd[i] == NULL)
		return (j);
	while (cmd[i])
		iterate_through_list(jb, cmd[i++]);
	return (j);
}

int				ft_bg(t_process *p, t_var **var)
{
	t_job		*job;
	char		*tmp;
	t_pos		*pos;

	job = find_job_by_id_bg(p->cmd, 1);
	if (job != NULL)
	{
		pos = to_stock(NULL, 1);
		pos->last_cmd_on_bg = 1;
		kill(-job->pgid, SIGCONT);
		job->status = 'r';
		ft_strdel(&tmp);
		return (0);
	}
	else if (p->cmd[1] == NULL)
		ft_printf_err("42sh: bg: no such job\n", p->fd_out);
	var = NULL;
	return (1);
}
