/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 12:36:04 by rlegendr    ###    #+. /#+    ###.fr     */
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

char        *check_backslash(char *ans, t_hist *hist)
{
	int        i;
	int        j;
	char    *newAns;
	i = 0;
	j = 0;
	if (ans[0] == '\0')
		return (ans);
	newAns = ft_strnew(ft_strlen(ans));
	while (ans && ans[i] != '\0')
	{
		if (ans[i] == 92 && ans[i + 1] == '\n')
			i++;
		else
			newAns[j++] = ans[i];
		i++;
	}
	newAns[j] = '\0';
	free(ans);
	replace_last_hist(hist, newAns);
	return (newAns);
}
