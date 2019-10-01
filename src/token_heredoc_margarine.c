/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_heredoc_margarine.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 15:38:36 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 18:19:39 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"


int				going_to_heredoc_end(t_pos *pos, int i)
{
	while (pos->ans[i])
	{
		if (i > 0 && pos->ans[i - 1] != 92)
		{
			if (pos->ans[i] == 32 || pos->ans[i] == '<' || pos->ans[i] == '>' ||
				pos->ans[i] == '&' || pos->ans[i] == '|' || pos->ans[i] == '\n'
				|| (pos->ans[i] == '$' && pos->ans[i + 1] == '{'))
				break ;
		}
		i++;
	}
	return (i);
}

// token_heredoc_creation.c

char			*remove_backslash(char *ans)
{
	int			i;
	int			j;
	char		*new;

	i = ft_strlen(ans);
	new = ft_strnew(i);
	ft_bzero(new, i);
	i = 0;
	j = 0;
	while (ans[i])
	{
		if (ans[i] != 92)
			new[j++] = ans[i];
		i++;
	}
	ft_strdel(&ans);
	return (new);
}

int				heredoc_found(t_pos *pos, int i, t_heredoc **hdoc, int j)
{
	int		save;

	j = i;
	save = i;
	while (pos->ans[i] && (pos->ans[i] == 32 || (pos->ans[i] >= 9 &&
			pos->ans[i] <= 13)))
		i++;
		i = going_to_heredoc_end(pos, i);
	while (pos->ans[j] && (pos->ans[j] == 32 || (pos->ans[j] >= 9 &&
			pos->ans[j] <= 13)))
		j++;
	if (pos->ans[j] && (pos->ans[j] == '<' || pos->ans[j] == '>' ||
			pos->ans[j] == '&' || pos->ans[j] == '|' || (pos->ans[j] == '$' &&
	pos->ans[j + 1] == '{')) && (i == 0 || (i > 0 && pos->ans[i - 1] != 92)) &&
			j == i)
		return (-1);
	*hdoc = add_list_back_heredoc(*hdoc);
	(*hdoc)->to_find = ft_strsub(pos->ans, j, i - j);
	j = ft_strlen((*hdoc)->to_find);
	if (j == 0)
		return (-1);
	while ((*hdoc)->to_find[--j] == 32)
		(*hdoc)->to_find[j] = '\0';
	(*hdoc)->to_find = remove_backslash((*hdoc)->to_find);
	return (1);
}

int				fill_hdoc_content(t_heredoc *hdoc, char *ans, int i, int j)
{
	while (i > 0 && ans[i] != '\n')
		i--;
	while (hdoc->next && hdoc->current_index == 1)
		hdoc = hdoc->next;
	if (ft_strcmp(ans + i + 1, hdoc->to_find) == 0)
	{
		hdoc->current_index = 1;
		hdoc->content = ft_strjoinf(hdoc->content, ans + i + 1, 1);
		hdoc->content = ft_strjoinf(hdoc->content, " ", 1);
		ft_strdel(&ans);
		if (hdoc->next == NULL)
			return (1);
		return (0);
	}
	j = i;
	while (ans[++j])
	{
		if (ans[j] == 32)
			ans[j] = -1;
	}
	hdoc->content = ft_strjoinf(hdoc->content, ans + i + 1, 1);
	hdoc->content = ft_strjoinf(hdoc->content, " ", 1);
	ft_strdel(&ans);
	return (0);
}
/*
void			print_hdoc(t_heredoc *hdoc)
{
	int		i;
	t_heredoc *tmp;

	tmp = hdoc;
	i = 0;
	if (hdoc == NULL)
	{
		ft_printf("{B.T.blue.}\nhdoc est null {eoc}\n");
		return ;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		ft_printf("{B.T.blue.}\nmaillon %d, to_find = '%s', current_index = %d, content = '%s'{eoc}\n", i, tmp->to_find, tmp->current_index, tmp->content);
		i++;
		tmp = tmp->next;
	}
	hdoc = tmp;
}
*/
void			free_hdoc(t_heredoc *hdoc)
{
	t_heredoc				*tmp;

	while (hdoc->prev)
		hdoc = hdoc->prev;
	while (hdoc)
	{
		tmp = hdoc;
		hdoc = hdoc->next;
		ft_strdel(&tmp->content);
		ft_strdel(&tmp->to_find);
		free(tmp);
	}
	free(hdoc);
}

t_heredoc		*search_for_heredocs_in_ans(t_pos *pos, int i, int open,
				t_heredoc *hdoc)
{
	while (pos->ans[i])
	{
		if (open != -1 && (pos->ans[i] == open ||
				(open == '$' && pos->ans[i] == '}')) && pos->ans[i - 1] != 92)
			open = -1;
		else if (open == -1 &&
				(pos->ans[i] == '"' || pos->ans[i] == 39 ||
				(pos->ans[i] == '$' && pos->ans[i + 1] == '{')) &&
				(i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
			open = pos->ans[i];
		if (open == -1 && pos->ans[i] == '<' && pos->ans[i + 1] == '<' &&
				(i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
		{
			if (heredoc_found(pos, i + 2, &hdoc, i + 2) == -1)
			{
				free_hdoc(hdoc);
				hdoc = NULL;
				pos->is_complete = 1;
			}
		}
		i++;
	}
	return (hdoc);
}

void		fill_ans_heredoc(t_heredoc **hdoc, t_pos *pos, int *i, int j)
{
	j = *i;
	while (pos->ans[*i])
	{
		if (pos->ans[*i] == '<' && pos->ans[*i + 1] == '<' && (*i == 0 || (*i > 0 && pos->ans[*i - 1] != 92)))
			break ;
		++*i;
	}
	if (pos->ans[*i])
		i += 2;
	while (pos->ans[*i] && (pos->ans[*i] == 32 || (pos->ans[*i] >= 9 &&
		pos->ans[*i] <= 13)))
		++*i;
	if (hdoc)
		*i += ft_strlen((*hdoc)->to_find);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, ft_strsub(pos->ans, j, *i - j), 3);
	if (!hdoc && (*i == -1))
		return ;
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, " ", 1);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, (*hdoc)->content, 1);
	*hdoc = (*hdoc)->next;
}

void			remake_pos_ans(t_heredoc *hdoc, t_pos *pos)
{
	int		i;
	int		j;

	i = 0;
	(void)hdoc;
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	ft_strdel(&pos->ans_heredoc);
	pos->ans_heredoc = ft_strnew(0);
	while (pos->ans[i])
		fill_ans_heredoc(&hdoc, pos, &i, j);
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	ft_strdel(&pos->ans_heredoc);
	pos->active_heredoc = 0;
	free_hdoc(pos->hdoc);
	pos->hdoc = NULL;
	pos->ans_heredoc_save = ft_secure_free(pos->ans_heredoc_save);
}

void			check_for_heredoc(t_pos *pos)
{
	int					i;
	char				open;

	i = 0;
	open = -1;
	if (pos->hdoc == NULL)
	{
		pos->ans_heredoc_save = ft_strdup(pos->ans);
		pos->ans_heredoc = ft_strdup(pos->ans);
		pos->hdoc = search_for_heredocs_in_ans(pos, i, open, pos->hdoc); //regarde s il y a des heredoc
	}
	else
	{
		while (pos->hdoc->prev)
			pos->hdoc = pos->hdoc->prev;
		if (fill_hdoc_content(pos->hdoc, ft_strdup(pos->ans),
					ft_strlen(pos->ans) - 1, ft_strlen(pos->ans) - 1))
		{
			pos->is_complete = 1;
//			pos->active_heredoc = 0;
			return ;
		}
	}
	if (pos->hdoc)
	{
		pos->is_complete = 0;
		pos->active_heredoc = 1;
	}
}
