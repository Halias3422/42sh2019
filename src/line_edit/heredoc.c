/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:30:08 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 14:09:10 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				heredoc_found(t_pos *pos, int i, int j)
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
	pos->hdoc = add_list_back_heredoc(pos->hdoc);
	(pos->hdoc)->to_find = ft_strsub(pos->ans, j, i - j);
	j = ft_strlen((pos->hdoc)->to_find);
	if (j == 0)
		return (-1);
	while ((pos->hdoc)->to_find[--j] == 32)
		(pos->hdoc)->to_find[j] = '\0';
	(pos->hdoc)->to_find = remove_backslash((pos->hdoc)->to_find);
	return (1);
}

int				fill_hdoc_content(t_pos *pos, char *ans, int i, int j)
{
	while (i > 0 && ans[i] != '\n')
		i--;
	while (pos->hdoc->next && pos->hdoc->current_index == 1)
		pos->hdoc = pos->hdoc->next;
	if (ft_strcmp(ans + i + 1, pos->hdoc->to_find) == 0)
	{
		pos->hdoc->current_index = 1;
		pos->hdoc->content = ft_strjoinf(pos->hdoc->content, ans + i + 1, 1);
		pos->hdoc->content = ft_strjoinf(pos->hdoc->content, " ", 1);
		ft_strdel(&ans);
		if (pos->hdoc->next == NULL)
			return (1);
		return (0);
	}
	j = i;
	while (ans[++j])
	{
		if (ans[j] == 32)
			ans[j] = -1;
	}
	pos->hdoc->content = ft_strjoinf(pos->hdoc->content, ans + i + 1, 1);
	pos->hdoc->content = ft_strjoinf(pos->hdoc->content, " ", 1);
	ft_strdel(&ans);
	return (0);
}

void			search_for_heredocs_in_ans(t_pos *pos, int i, int open)
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
			if (heredoc_found(pos, i + 2, i + 2) == -1)
			{
				free_hdoc(pos->hdoc);
				pos->hdoc = NULL;
				pos->is_complete = 1;
			}
		}
		i++;
	}
}

void			check_for_heredoc(t_pos *pos, int i, char open)
{
	if (pos->hdoc == NULL)
	{
		pos->ans_heredoc_save = ft_strdup(pos->ans);
		pos->ans_heredoc = ft_strdup(pos->ans);
		search_for_heredocs_in_ans(pos, i, open);
	}
	else
	{
		while (pos->hdoc->prev)
			pos->hdoc = pos->hdoc->prev;
		if (fill_hdoc_content(pos, ft_strdup(pos->ans),
					ft_strlen(pos->ans) - 1, ft_strlen(pos->ans) - 1))
		{
			pos->is_complete = 1;
			return ;
		}
	}
	if (pos->hdoc)
	{
		pos->is_complete = 0;
		pos->active_heredoc = 1;
	}
}
