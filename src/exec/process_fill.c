/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_fill.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 17:07:12 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 18:12:53 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

void		fill_process_split(t_job **j, t_lexeur **res, int i)
{
	int		k;

	k = i;
	while (res[k] && (res[k]->word || (res[k]->token == 4 ||
	res[k]->token == 5 || res[k]->token == 6 || res[k]->token == 7)))
	{
		k++;
	}
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

char		*add_space_content(char *content)
{
	char 	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(content) + 1));
	while (content[i])
	{
		if (content[i] == -1)
			res[i] = ' ';
		else
			res[i] = content[i];
		i++;
	}
	res[i] = '\0';
	ft_strdel(&content);
	return (res);
}

char		*get_content(char *tag, t_lexeur **res, int *t)
{
	char	*content;

	(*t)++;
	content = NULL;
	while (res[*t] && ft_strcmp(res[*t]->word, tag))
	{
		if (!content)
			content = ft_strdup(res[*t]->word);
		else
			ft_strjoin_free(&content, res[*t]->word);
		if (res[*t + 1] && ft_strcmp(res[*t + 1]->word, tag))
			ft_strjoin_free(&content, "\n");
		(*t)++;
	}
	(*t)++;
//	printf("CONTENT: _%s_\n", content);
	content = add_space_content(content);
	return (content);
}

void		fill_heredoc(t_lexeur **res, t_redirect *tmp, int *t)
{
	int		i;

	i = 0;
	tmp->token = ft_strdup(g_fill_token[res[*t]->token].name);
	printf("tmp->token: _%s_\n", tmp->token);
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	tmp->heredoc_content = get_content(res[*t]->redirection, res, t);
	tmp->fd_out = NULL;
	tmp->next = NULL;
}

void		fill_ag_first(t_redirect *tmp, t_lexeur **res, int *t)
{
	tmp->heredoc_content = NULL;
	if (res[*t]->token == 7)
		return (fill_heredoc(res, tmp, t));
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
	{
		tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	}
	else
	{
		tmp->fd = 1;
	}
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
	tmp->heredoc_content = NULL;
	if (res[*t]->token == 7)
		return (fill_heredoc(res, tmp, t));
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
		tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	else
		tmp->fd = 1;
	tmp->token = (res[*t]->token) ? ft_strdup(g_fill_token[res[*t]->token].name)
	: NULL;
	tmp->next = NULL;
}

void			go_next_heredoc(t_lexeur **res, int *i)
{
	char	*tag;

	tag = ft_strdup(res[*i]->redirection);
	(*i)++;
	while (res[*i])
	{
		if (!ft_strcmp(res[*i]->word, tag))
			break ;
		(*i)++;
	}
	if (res[*i])
		(*i)++;
	ft_strdel(&tag);
}

void		fill_all_cmd(t_lexeur **res, t_job **j, int *k, int i)
{
	while (res[i] && ((res[i]->word) || (res[i]->token == 4 ||
	res[i]->token == 5 || res[i]->token == 6 || res[i]->token == 7
	|| res[i]->token == 8 || res[i]->token == 9)))
	{
		if (res[i]->token == 7)
			go_next_heredoc(res, &i);
		if (res[i] && res[i]->word)
		{
			(*j)->p->cmd[*k] = ft_strdup(res[i]->word);
			(*k)++;
		}
		if (res[i])
			i++;
	}
}
