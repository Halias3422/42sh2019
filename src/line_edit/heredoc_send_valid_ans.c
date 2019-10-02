/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc_send_valid_ans.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:56:46 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 13:44:28 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int			fill_ans_heredoc(t_pos *pos, int i, int j)
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
	if (pos->hdoc)
		i += ft_strlen(pos->hdoc->to_find);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc,
			ft_strsub(pos->ans, j, i - j), 3);
	if (pos->hdoc == NULL)
		return(ft_strlen(pos->ans));
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, " ", 1);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, pos->hdoc->content, 1);
	pos->hdoc = pos->hdoc->next;
	return (i);
}

void			remake_pos_ans(t_pos *pos)
{
	int			i;
	t_heredoc	*tmp;

	i = 0;
	tmp = pos->hdoc;
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	pos->ans_heredoc = ft_secure_free(pos->ans_heredoc);
	pos->ans_heredoc = ft_strnew(0);
	while (pos->ans[i])
		i = fill_ans_heredoc(pos, i, 0);
	pos->hdoc = tmp;
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	pos->ans_heredoc = ft_secure_free(pos->ans_heredoc);
	pos->active_heredoc = 0;
	free_hdoc(pos->hdoc);
	pos->hdoc = NULL;
	pos->ans_heredoc_save = ft_secure_free(pos->ans_heredoc_save);
}
