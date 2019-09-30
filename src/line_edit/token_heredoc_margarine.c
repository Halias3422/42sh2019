/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_heredoc_margarine.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 15:38:36 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 23:17:51 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"




// token_heredoc_creation.c

int				heredoc_found(t_pos *pos, int i, t_heredoc **hdoc)
{
	int		save;
	int		j;

	j = i;
	save = i;
	while (pos->ans[i] && pos->ans[i] != '<' && pos->ans[i] != '&' &&
	pos->ans[i] != '|' && pos->ans[i] != '>' && !(pos->ans[i] == '$' &&
		pos->ans[i + 1] == '{') && (i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
		i++;
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
	while ((*hdoc)->to_find[--j] == 32)
		(*hdoc)->to_find[j] = '\0';
	return (1);
}

int				fill_hdoc_content(t_heredoc *hdoc, char *ans, int i)
{
	int		j;

	while (i > 0 && ans[i] != '\n')
		i--;
	while (hdoc->next && hdoc->current_index == 1)
		hdoc = hdoc->next;
	if (ft_strcmp(ans + i + 1, hdoc->to_find) == 0)
	{
		hdoc->current_index = 1;
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

void			free_hdoc(t_heredoc *hdoc)
{
	t_heredoc				*tmp;

	while (hdoc)
	{
		tmp = hdoc;
		hdoc = hdoc->next;
		ft_strdel(&tmp->content);
		ft_strdel(&tmp->to_find);
	}
	free(hdoc);
}

void			search_for_heredocs_in_ans(t_pos *pos, int i, int open,
				t_heredoc **hdoc)
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
		if (pos->ans[i] == '<' && pos->ans[i + 1] == '<' &&
				(i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
		{
			if (heredoc_found(pos, i + 2, hdoc) == -1)
			{
				free_hdoc(*hdoc);
				pos->is_complete = 1;
			}
		}
		i++;
	}
}

void			check_for_heredoc(t_pos *pos)
{
	int					i;
	char				open;
	static t_heredoc	*hdoc = NULL;

	i = 0;
	open = -1;
	if (hdoc == NULL)
		search_for_heredocs_in_ans(pos, i, open, &hdoc);
	else
	{
		while (hdoc->prev)
			hdoc = hdoc->prev;
		if (fill_hdoc_content(hdoc, ft_strdup(pos->ans),
					ft_strlen(pos->ans) - 1))
		{
			pos->is_complete = 1;
			free_hdoc(hdoc);
			return ;
		}
	}
	if (hdoc)
		pos->is_complete = 0;
}
