/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc_send_valid_ans.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:56:46 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 19:02:06 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int			fill_ans_heredoc(t_heredoc **hdoc, t_pos *pos, int i, int j)
{
	j = i;
	while (pos->ans[i])
	{
		if (pos->ans[i] == '<' && pos->ans[i + 1] == '<' &&
			(i == 0 || (i > 0 && pos->ans[i - 1] != 92)))
			break ;
		i += 1;
	}
	if (pos->ans[i])
		i += 2;
	while (pos->ans[i] && (pos->ans[i] == 32 || (pos->ans[i] >= 9 &&
		pos->ans[i] <= 13)))
		i += 1;
	if (*hdoc)
		i += ft_strlen((*hdoc)->to_find);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc,
			ft_strsub(pos->ans, j, i - j), 3);
	if (!(*hdoc))
		return(ft_strlen(pos->ans));
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, " ", 1);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, (*hdoc)->content, 1);
	*hdoc = (*hdoc)->next;
	return (i);
}

void			remake_pos_ans(t_heredoc *hdoc, t_pos *pos)
{
	int		i;

	i = 0;
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	ft_strdel(&pos->ans_heredoc);
	pos->ans_heredoc = ft_strnew(0);
	while (pos->ans[i])
		i = fill_ans_heredoc(&hdoc, pos, i, 0);
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	ft_strdel(&pos->ans_heredoc);
	pos->active_heredoc = 0;
	free_hdoc(pos->hdoc);
	pos->hdoc = NULL;
	pos->ans_heredoc_save = ft_secure_free(pos->ans_heredoc_save);
}
