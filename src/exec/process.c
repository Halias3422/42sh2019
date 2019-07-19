/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 14:34:20 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/19 03:36:51 by mdelarbr    ###    #+. /#+    ###.fr     */
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
		i++;
		nb++;
	}
	return (nb);
}

void		fill_cmd(t_lexeur **res, t_job **j, int *k, int *i)
{
	if (res[*i]->fd != -1)
	{
		(*j)->p->fd = res[*i]->fd;
	}
	if (!res[*i]->redirection)
		(*j)->p->redirection = ft_strdup("");
	else
		(*j)->p->redirection = ft_strdup(res[*i]->redirection);
	if (res[*i]->word)
	{
		(*j)->p->cmd[*k] = ft_strdup(res[*i]->word);
		(*k)++;
	}
	(*i)++;
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

char		*find_fill_token(t_lexeur **ar, int i)
{
	char	*res;
	int		j;

	j = 0;
	res = NULL;
	while (j < i)
	{
		if (ar[j]->token == (enum e_token)4)
			return (ft_strdup(">>"));
		if (ar[j]->token == (enum e_token)5)
			return (ft_strdup(">"));
		if (ar[j]->token == (enum e_token)6)
			return (ft_strdup("<<"));
		if (ar[j]->token == (enum e_token)7)
			return (ft_strdup("<"));
		j++;
	}
	return (res);
}

int			fill_process_while(t_lexeur **res, t_job **j, t_process **start,
int *i)
{
	int		k;

	k = 0;
	fill_process_split(j, res, i);
	(*j)->p->fd = -1;
	(*j)->p->cmd = malloc(sizeof(char *) * (cnt_process(res, *i) + 1));
	while (res[*i] && (res[*i]->word || res[*i]->redirection || res[*i]->token == 4 || res[*i]->token == 5))
		fill_cmd(res, j, &k, i);
	(*j)->p->cmd[k] = NULL;
	(*j)->p->token = find_fill_token(res, *i);
	if (res[*i] && (res[*i]->token == 2 || res[*i]->token == 3
	|| res[*i]->token == 0))
	{
		(*j)->p->next = malloc(sizeof(t_process));
		(*j)->p = (*j)->p->next;
		(*j)->p->status = '\0';
	}
	else if ((res[*i] && (*j)->next != NULL) && (res[*i]->token == 1 ||
	res[*i]->token == 8))
		change_job(j, start);
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
	j->p->status = '\0';
	while (res[i])
	{
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
