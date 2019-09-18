/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_fill.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 17:07:12 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 17:14:10 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

void		fill_process_split(t_job **j, t_lexeur **res, int *i)
{
	int		k;

	k = (*i);
	while (res[k] && (res[k]->word || (res[k]->token == 4 ||
	res[k]->token == 5 || res[k]->token == 6 || res[k]->token == 7)))
		k++;
	if (res[k] && res[k]->token == 0)
		(*j)->p->split = 'A';
	else if (res[k] && res[k]->token == 2)
		(*j)->p->split = '|';
	else if (res[k] && res[k]->token == 3)
		(*j)->p->split = 'P';
	else
		(*j)->p->split = '\0';
}

void		fill_token(t_process *p, t_lexeur **res, int *i)
{
	if (res[*i]->token == 9)
	{
		p->redirect->token = ft_strdup("<");
		(*i)++;
	}
	else if (res[*i]->token == 6)
	{
		p->redirect->token = ft_strdup(">");
		(*i)++;
	}
	else if (res[*i]->token == 4)
	{
		p->redirect->token = ft_strdup(">>");
		(*i)++;
	}
	else if (res[*i]->token == 7)
	{
		p->redirect->token = ft_strdup("<<");
		(*i)++;
	}
	else
		p->redirect->token = NULL;
}

void		fill_ag_first(t_redirect *tmp, t_lexeur **res, int *t)
{
	if (res[*t]->token != 4 && res[*t]->token != 6 && res[*t]->token != 9)
	{
		tmp->fd_in = (res[*t]->fd_in) ? ft_strdup(res[*t]->fd_in) : NULL;
		tmp->fd_out = (res[*t]->fd_out) ? ft_strdup(res[*t]->fd_out) : NULL;
	}
	else
	{
		tmp->fd_in = NULL;
		tmp->fd_out = (res[*t]->redirection) ? ft_strdup(res[*t]->redirection)
		: NULL;
	}
	if (res[*t]->token == 4 || res[*t]->token == 6 || res[*t]->token == 9)
		tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 0;
	else
		tmp->fd = 0;
	tmp->token = (res[*t]->token) ? ft_strdup(g_fill_token[res[*t]->token].name)
	: NULL;
	tmp->next = NULL;
}

void		fill_ag_next(t_redirect *tmp, t_lexeur **res, int *t)
{
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_redirect));
	tmp = tmp->next;
	if (res[*t]->token != 4 && res[*t]->token != 6 && res[*t]->token != 9)
	{
		tmp->fd_in = (res[*t]->fd_in) ? ft_strdup(res[*t]->fd_in) : NULL;
		tmp->fd_out = (res[*t]->fd_out) ? ft_strdup(res[*t]->fd_out) : NULL;
	}
	else
	{
		tmp->fd_in = NULL;
		tmp->fd_out = (res[*t]->redirection) ? ft_strdup(res[*t]->redirection)
		: NULL;
	}
	if (res[*t]->token == 4 || res[*t]->token == 6 || res[*t]->token == 9)
		tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 0;
	else
		tmp->fd = 0;
	tmp->token = (res[*t]->token) ? ft_strdup(g_fill_token[res[*t]->token].name)
	: NULL;
	tmp->next = NULL;
}

void		fill_all_cmd(t_lexeur **res, t_job **j, int *k, int i)
{
	while (res[i] && ((res[i]->word) || (res[i]->token == 4 ||
	res[i]->token == 5 || res[i]->token == 6 || res[i]->token == 7
	|| res[i]->token == 8 || res[i]->token == 9)))
	{
		if (res[i]->word)
		{
			(*j)->p->cmd[*k] = ft_strdup(res[i]->word);
			(*k)++;
		}
		i++;
	}
}
