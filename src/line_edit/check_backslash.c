/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 09:26:10 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	replace_last_hist(t_hist *hist, char *ans)
{
	while (hist->next)
		hist = hist->next;
	hist = hist->prev;
	free(hist->cmd);
	hist->cmd = ft_strdup(ans);
}

char        *check_backslash(t_pos *pos, t_hist *hist)
{
	int		i;
	int		j;
	char	*new_ans;

	i = 0;
	j = 0;
	if (pos->ans[0] == '\0' || ft_strchr(pos->ans, 92) == NULL)
		return (pos->ans);
	new_ans = ft_strnew(ft_strlen(pos->ans));
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (pos->ans[i] == 92 && pos->ans[i + 1] == '\n')
			i++;
		else
			new_ans[j++] = pos->ans[i];
		i++;
	}
	new_ans[j] = '\0';
	pos->ans = ft_secure_free(pos->ans);
	replace_last_hist(hist, new_ans);
	return (new_ans);
}
