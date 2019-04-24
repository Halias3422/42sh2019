/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_entry.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 07:21:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 10:13:38 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

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

t_hist			*entry_is_incomplete(t_pos *pos, t_hist *hist, char *buf)
{
	input_is_printable_char(pos, buf);
	pos->history_mode = 0;
	pos->act_li = pos->start_li + get_len_with_lines(pos) / pos->max_co;
	pos->act_co = pos->len_prompt;
	clean_screen(pos);
	print_ans_start(pos, buf);
	return (hist);
}

t_hist			*entry_is_complete(t_pos *pos, t_hist *hist)
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

t_hist			*input_is_entry(t_pos *pos, t_hist *hist, char *buf)
{
	pos->is_complete = find_missing_quote(pos->ans);
	if (pos->is_complete == 0)
		entry_is_incomplete(pos, hist, buf);
	else
		entry_is_complete(pos, hist);
	return (hist);
}
