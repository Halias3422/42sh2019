/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   1_input_is_entry.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 13:04:32 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 09:21:11 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"



t_hist		*input_is_complete(t_pos *pos, t_hist *hist)
{
	while (hist->next)
		hist = hist->next;
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	if (ft_strlen(pos->ans) == 0)
		return (hist);
	if ((hist->prev && ft_strcmp(pos->ans, hist->prev->cmd) == 0))
	{
		hist->cmd = ft_secure_free(hist->cmd);
		return (hist->prev);
	}
	write(pos->history, pos->ans, ft_strlen(pos->ans));
	write(pos->history, "\n", 1);
	while (hist->next)
		hist = hist->next;
	if (hist->cmd)
		hist->cmd = ft_secure_free(hist->cmd);
	hist->cmd = ft_strdup(pos->ans);
	hist = add_list_back_hist(hist);
	hist = hist->prev;
	return (hist);
}

int			find_missing_quote(char *str)
{
	int		i;
	int		nb_quote;

	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			nb_quote += 1;
		i++;
	}
	if (nb_quote % 2 == 0)
		return (1);
	return (0);
}
