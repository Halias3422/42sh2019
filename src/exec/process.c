/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 14:34:20 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 17:44:56 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

int			cnt_process(t_lexeur **res, int i)
{
	int		nb;

	nb = 0;
	while (res[i])
	{
		if (res[i]->word)
			nb++;
		i++;
	}
	return (nb);
}

void		change_job(t_job **j, t_process **start)
{
	(*j)->p->next = NULL;
	(*j)->p = *start;
	(*j) = (*j)->next;
	(*j)->p = malloc(sizeof(t_process));
	*start = (*j)->p;

}

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

void		fill_process_file(t_process *p, t_lexeur **res, int i)
{
	if (res[i]->fd_in)
		p->file_in = ft_strdup(res[i]->fd_in);
	if (res[i]->fd_out)
		p->file_out = ft_strdup(res[i]->fd_out);
}

void		fill_token(t_process *p, t_lexeur **res, int *i)
{
	if (res[*i]->token == 9)
	{
		p->token = ft_strdup("<");
		(*i)++;
	}
	else if (res[*i]->token == 6)
	{
		p->token = ft_strdup(">");
		(*i)++;
	}
	else if (res[*i]->token == 4)
	{
		p->token = ft_strdup(">>");
		(*i)++;
	}
	else if (res[*i]->token == 7)
	{
		p->token = ft_strdup("<<");
		(*i)++;
	}
	else
		p->token = NULL;
}

t_redirect		*fill_agregator(t_redirect *p, t_lexeur **res, int *i)
{
	int			t;
	int			done;
	t_redirect	*tmp;

	done = 0;
	t = 0;
	tmp = NULL;
	while (res[t])
	{
		if (res[t] && (res[t]->token == 5 || res[t]->token == 8))
		{
			if (!tmp)
			{
				tmp = malloc(sizeof(t_redirect));
				p = tmp;
				tmp->fd_in = (res[t]->fd_in) ? ft_strdup(res[t]->fd_in) : NULL;
				tmp->fd_out = (res[t]->fd_out) ? ft_strdup(res[t]->fd_out) : NULL;
				tmp->next = NULL;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = malloc(sizeof(t_redirect));
				tmp = tmp->next;
				tmp->fd_in = (res[t]->fd_in) ? ft_strdup(res[t]->fd_in) : NULL;
				tmp->fd_out = (res[t]->fd_out) ? ft_strdup(res[t]->fd_out) : NULL;
				tmp->next = NULL;
			}
			done++;
		}
		t++;
	}
	(*i) += done;
	return (p);
}

void		fill_cmd(t_lexeur **res, t_job **j, int *k, int *i)
{
	if (res[*i])
		fill_token((*j)->p, res, i);
	(*j)->p->cmd[*k] = ft_strdup(res[*i]->word);
	(*k)++;
	(*i)++;
}

int			fill_process_while(t_lexeur **res, t_job **j, t_process **start,
int *i)
{
	int		k;

	k = 0;
	fill_process_split(j, res, i);
	(*j)->p->cmd = malloc(sizeof(char *) * (cnt_process(res, *i) + 1));
	while (res[*i] && res[*i]->word)
		fill_cmd(res, j, &k, i);
	(*j)->p->cmd[k] = NULL;
	(*j)->p->builtin = test_builtin((*j)->p);
//	if (res[*i] && (res[*i]->fd_in || res[*i]->fd_out))
//		fill_process_file((*j)->p, res, *i);
	if (res[*i])
		fill_token((*j)->p, res, i);
	if (res[*i])
		(*j)->p->redirect = fill_agregator(NULL, res, i);
	//printf("res[%d]: _%d_\n", *i, res[*i]->token);
	if (res[*i] && (res[*i]->token == 0 && res[*i]->token == 2))
	{
		(*j)->p->next = malloc(sizeof(t_process));
		(*j)->p = (*j)->p->next;
		(*j)->p->status = '\0';
	}
	else if ((res[*i] && (*j)->next != NULL) && (res[*i]->token == 1 ||
	res[*i]->token == 10))
	{
		change_job(j, start);
	}
	else
	{
		(*j)->p->next = NULL;
		(*j)->p = *start;
		return (0);
	}
	return (1);
}

void		fill_process(t_job *j, t_lexeur **res)
{
	int			i;
	t_process	*start;

	i = 0;
	j->p = malloc(sizeof(t_process));
	start = j->p;
	while (res[i])
	{
		j->p->file_in = NULL;
		j->p->file_out = NULL;
		j->p->status = '\0';
		j->p->stoped = 0;
		j->p->completed = 0;
		j->p->redirect = NULL;
		if (fill_process_while(res, &j, &start, &i) == 0)
			break ;
		i++;
	}
}

void		free_process(t_job *j)
{
	t_process *buf;

	while (j->p)
	{
		buf = j->p->next;
		free(j->p->token);
		free(j->p);
		j->p = buf;
	}
}
