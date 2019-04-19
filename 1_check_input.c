/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:01:51 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 08:41:27 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		free_t_hist(t_hist *hist)
{
	t_hist *tmp;

	while (hist->next)
		hist = hist->next;
	while (hist)
	{
		tmp = hist;
		if (hist->cmd)
			hist->cmd = ft_secure_free(hist->cmd);
		hist = hist->prev;
		tmp = ft_secure_free(tmp);
	}
}

t_hist		*input_is_entry(t_pos *pos, t_hist *hist)
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

void		input_is_backspace(t_pos *pos)
{
	if ((pos->is_complete == 1 && (pos->let_nb > 0 || pos->act_li >
	pos->start_li)) || (pos->is_complete == 0 && pos->act_co > pos->len_prompt))
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		remove_char_ans(pos);
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
		pos->len_ans -= 1;
	}
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

t_hist		*check_input(char *buf, t_pos *pos, t_hist *hist, t_inter *inter)
{
	(void)inter;
	if (buf[0] == 27)
		hist = find_arrow(buf, pos, hist);
	else
	{
		bzero(buf + 1, 3);
		if (buf[0] == 127)
			input_is_backspace(pos);
		else
		{
			if (buf[0] == 10)
			{
				if ((pos->is_complete = find_missing_quote(pos->ans)) == 0)
				{
					input_is_printable_char(pos, buf);
					if (pos->act_li == pos->max_li)
						pos->start_li -= 1;
					else
						pos->act_li += 1;
					pos->act_co = pos->len_prompt;
					write(1, "\n> ", 3);
				}
				if (pos->is_complete == 1)
					hist = input_is_entry(pos, hist);
			}
			else
				input_is_printable_char(pos, buf);
		}
		pos->saved_ans = ft_secure_free(pos->saved_ans);
		if (buf[0] != 10)
			pos->saved_ans = ft_strdup(pos->ans);
		if (hist && hist->next == NULL && pos->is_complete == 1)
		{
			if (hist->cmd != NULL)
				hist->cmd = ft_secure_free(hist->cmd);
			hist->cmd = ft_strdup(pos->ans);
		}
		if (pos->ans[0] == '\0')
			pos->history_mode = 0;
	}
	clean_screen(pos);
	print_ans(pos, buf);
	return (hist);
}
