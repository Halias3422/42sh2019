/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 13:46:29 by rlegendr    ###    #+. /#+    ###.fr     */
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
	hist->cmd = ft_strnew(ft_strlen(ans));
	hist->cmd = ft_strcpy(hist->cmd, ans);
}

char        *check_backslash(t_pos *pos, t_hist *hist)
{
	int		i;
	int		j;
	char	*newAns;

	i = 0;
	j = 0;
	if (pos->ans[0] == '\0')
		return (pos->ans);
	newAns = ft_strnew(ft_strlen(pos->ans));
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (pos->ans[i] == 92 && pos->ans[i + 1] == '\n')
			i++;
		else
			newAns[j++] = pos->ans[i];
		i++;
	}
	newAns[j] = '\0';
	pos->ans = ft_secure_free(pos->ans);
	replace_last_hist(hist, newAns);
	return (newAns);
}
